#ifndef _TRAP_BLOCKINGQUEUE_H_
#define _TRAP_BLOCKINGQUEUE_H_

namespace TRAP
{
	template<typename T>
	class BlockingQueue
	{
	public:
		/// <summary>
		/// Push a copy constructable item to the queue.
		/// </summary>
		/// <param name="item">Item to push.</param>
		template<typename Q = T>
		typename std::enable_if<std::is_copy_constructible<Q>::value, void>::type
		Push(const T& item);

		/// <summary>
		/// Push a move constructable item to the queue.
		/// </summary>
		/// <param name="item">Item to push.</param>
		template<typename Q = T>
		typename std::enable_if<std::is_move_constructible<Q>::value, void>::type
		Push(T&& item);

		/// <summary>
		/// Try to push a copy constructable item to the queue.
		/// </summary>
		/// <param name="item">Item to push.</param>
		/// <returns>True on success, false otherwise.</returns>
		template<typename Q = T>
		typename std::enable_if<std::is_copy_constructible<Q>::value, bool>::type
		TryPush(const T& item);

		/// <summary>
		/// Try to push a move constructable item to the queue.
		/// </summary>
		/// <param name="item">Item to push.</param>
		/// <returns>True on success, false otherwise.</returns>
		template<typename Q = T>
		typename std::enable_if<std::is_move_constructible<Q>::value, bool>::type
		TryPush(T&& item);

		/// <summary>
		/// Pop a copy assignable item from the queue.
		/// </summary>
		/// <param name="item">Item to pop.</param>
		template<typename Q = T>
		typename std::enable_if<std::is_copy_assignable<Q>::value && !std::is_move_assignable<Q>::value, bool>::type
		Pop(T& item);

		/// <summary>
		/// Pop a move assignable item from the queue.
		/// </summary>
		/// <param name="item">Item to pop.</param>
		template<typename Q = T>
		typename std::enable_if<std::is_move_assignable<Q>::value, bool>::type
		Pop(T& item);

		/// <summary>
		/// Try to pop a copy assignable item from the queue.
		/// </summary>
		/// <param name="item">Item to pop.</param>
		/// <returns>True on success, false otherwise.</returns>
		template<typename Q = T>
		typename std::enable_if<std::is_copy_assignable<Q>::value && !std::is_move_assignable<Q>::value, bool>::type
		TryPop(T& item);

		/// <summary>
		/// Try to pop a move assignable item from the queue.
		/// </summary>
		/// <param name="item">Item to pop.</param>
		/// <returns>True on success, false otherwise.</returns>
		template<typename Q = T>
		typename std::enable_if<std::is_move_assignable<Q>::value, bool>::type
		TryPop(T& item);

		/// <summary>
		/// Mark the queue as done.
		/// </summary>
		void Done() noexcept;

		/// <summary>
		/// Check if queue is empty.
		/// </summary>
		/// <returns>True if queue is empty, false otherwise.</returns>
		bool Empty() const noexcept;

		/// <summary>
		/// Retrieve the size of the queue.
		/// </summary>
		/// <returns>Queue size.</returns>
		uint32_t Size() const noexcept;

	private:
		std::queue<T> m_queue{};
		mutable std::mutex m_mutex;
		std::condition_variable m_ready;
		bool m_done = false;
	};
}

//-------------------------------------------------------------------------------------------------------------------//

template <typename T>
template <typename Q>
typename std::enable_if<std::is_copy_constructible<Q>::value, void>::type TRAP::BlockingQueue<T>::Push(const T& item)
{
	{
		std::unique_lock lock(m_mutex);
		m_queue.push(item);
	}

	m_ready.notify_one();
}

//-------------------------------------------------------------------------------------------------------------------//

template <typename T>
template <typename Q>
typename std::enable_if<std::is_move_constructible<Q>::value, void>::type TRAP::BlockingQueue<T>::Push(T&& item)
{
	{
		std::unique_lock lock(m_mutex);
		m_queue.emplace(std::forward<T>(item));
	}

	m_ready.notify_one();
}

//-------------------------------------------------------------------------------------------------------------------//

template <typename T>
template <typename Q>
typename std::enable_if<std::is_copy_constructible<Q>::value, bool>::type TRAP::BlockingQueue<T>::TryPush(const T& item)
{
	{
		const std::unique_lock lock(m_mutex, std::try_to_lock);
		if (!lock)
			return false;

		m_queue.push(item);
	}

	m_ready.notify_one();
	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

template <typename T>
template <typename Q>
typename std::enable_if<std::is_move_constructible<Q>::value, bool>::type TRAP::BlockingQueue<T>::TryPush(T&& item)
{
	{
		const std::unique_lock lock(m_mutex, std::try_to_lock);
		if (!lock)
			return false;

		m_queue.emplace(std::forward<T>(item));
	}

	m_ready.notify_one();
	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

template <typename T>
template <typename Q>
typename std::enable_if<std::is_copy_assignable<Q>::value && !std::is_move_assignable<Q>::value, bool>::type TRAP::BlockingQueue<T>::Pop(T& item)
{
	std::unique_lock lock(m_mutex);
	while (m_queue.empty() && !m_done)
		m_ready.wait(lock);

	if (m_queue.empty())
		return false;

	item = m_queue.front();
	m_queue.pop();

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

template <typename T>
template <typename Q>
typename std::enable_if<std::is_move_assignable<Q>::value, bool>::type TRAP::BlockingQueue<T>::Pop(T& item)
{
	std::unique_lock lock(m_mutex);
	while (m_queue.empty() && !m_done)
		m_ready.wait(lock);

	if (m_queue.empty())
		return false;

	item = std::move(m_queue.front());
	m_queue.pop();

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

template <typename T>
template <typename Q>
typename std::enable_if<std::is_copy_assignable<Q>::value && !std::is_move_assignable<Q>::value, bool>::type TRAP::BlockingQueue<T>::TryPop(T& item)
{
	const std::unique_lock lock(m_mutex, std::try_to_lock);
	if (!lock || m_queue.empty())
		return false;

	item = m_queue.front();
	m_queue.pop();
	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

template <typename T>
template <typename Q>
typename std::enable_if<std::is_move_assignable<Q>::value, bool>::type TRAP::BlockingQueue<T>::TryPop(T& item)
{
	const std::unique_lock lock(m_mutex, std::try_to_lock);
	if (!lock || m_queue.empty())
		return false;

	item = std::move(m_queue.front());
	m_queue.pop();

	return true;
}

//-------------------------------------------------------------------------------------------------------------------//

template <typename T>
void TRAP::BlockingQueue<T>::Done() noexcept
{
	{
		std::unique_lock lock(m_mutex);
		m_done = true;
	}

	m_ready.notify_all();
}

//-------------------------------------------------------------------------------------------------------------------//

template <typename T>
bool TRAP::BlockingQueue<T>::Empty() const noexcept
{
	std::scoped_lock lock(m_mutex);
	return m_queue.empty();
}

//-------------------------------------------------------------------------------------------------------------------//

template <typename T>
uint32_t TRAP::BlockingQueue<T>::Size() const noexcept
{
	std::scoped_lock lock(m_mutex);
	return m_queue.size();
}

#endif /*_TRAP_BLOCKINGQUEUE_H_*/
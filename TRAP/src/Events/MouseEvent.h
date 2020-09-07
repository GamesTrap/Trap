#ifndef _TRAP_MOUSEEVENT_H_
#define _TRAP_MOUSEEVENT_H_

#include "Input/Input.h"
#include "Event.h"

namespace TRAP::Events
{
	class MouseMoveEvent final : public Event
	{
	public:
		MouseMoveEvent(float x, float y, std::string title);

		float GetX() const;
		float GetY() const;
		Math::Vec2 GetPosition() const;
		const std::string& GetTitle() const;

		std::string ToString() const override;

		static EventType GetStaticType();
		EventType GetEventType() const override;
		const char* GetName() const override;
		int32_t GetCategoryFlags() const override;

	private:
		float m_mouseX, m_mouseY;
		std::string m_title;
	};

	class MouseScrollEvent final : public Event
	{
	public:
		MouseScrollEvent(float xOffset, float yOffset, std::string title);

		float GetXOffset() const;
		float GetYOffset() const;
		Math::Vec2 GetOffset() const;
		const std::string& GetTitle() const;

		std::string ToString() const override;

		static EventType GetStaticType();
		EventType GetEventType() const override;
		const char* GetName() const override;
		int32_t GetCategoryFlags() const override;

	private:
		float m_xOffset, m_yOffset;
		std::string m_title;
	};

	class MouseButtonEvent : public Event
	{
	public:
		Input::MouseButton GetMouseButton() const;

		int32_t GetCategoryFlags() const override;

	protected:
		explicit MouseButtonEvent(Input::MouseButton button);

		static std::string MouseButtonToString(Input::MouseButton button);

		Input::MouseButton m_button;
	};

	class MouseButtonPressEvent final : public MouseButtonEvent
	{
	public:
		explicit MouseButtonPressEvent(Input::MouseButton button, std::string title);

		const std::string& GetTitle() const;
		
		std::string ToString() const override;

		static EventType GetStaticType();
		EventType GetEventType() const override;
		const char* GetName() const override;

	private:
		std::string m_title;
	};

	class MouseButtonReleaseEvent final : public MouseButtonEvent
	{
	public:
		explicit MouseButtonReleaseEvent(Input::MouseButton button, std::string title);

		const std::string& GetTitle() const;

		std::string ToString() const override;

		static EventType GetStaticType();
		EventType GetEventType() const override;
		const char* GetName() const override;

	private:
		std::string m_title;
	};

	class MouseEnterEvent final : public Event
	{
	public:
		explicit MouseEnterEvent(std::string title);

		const std::string& GetTitle() const;

		static EventType GetStaticType();
		EventType GetEventType() const override;
		const char* GetName() const override;
		int32_t GetCategoryFlags() const override;

	private:
		std::string m_title;
	};

	class MouseLeaveEvent final : public Event
	{
	public:
		explicit MouseLeaveEvent(std::string title);

		const std::string& GetTitle() const;

		static EventType GetStaticType();
		EventType GetEventType() const override;
		const char* GetName() const override;
		int32_t GetCategoryFlags() const override;

	private:
		std::string m_title;
	};
}

#endif /*_TRAP_MOUSEEVENT_H_*/
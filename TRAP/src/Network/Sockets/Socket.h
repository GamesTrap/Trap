/*
////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2019 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

Modified by: Jan "GamesTrap" Schuerkamp
*/

#ifndef _TRAP_NETWORK_SOCKET_H_
#define _TRAP_NETWORK_SOCKET_H_

#include "SocketHandle.h"

namespace TRAP::Network
{
	class SocketSelector;

	class Socket
	{
	public:
		/// <summary>
		/// Default Constructor.
		/// </summary>
		Socket() = default;
		/// <summary>
		/// Default Move Constructor.
		/// </summary>
		Socket(Socket&&) = default;
		/// <summary>
		/// Default Move Assignment Operator.
		/// </summary>
		Socket& operator=(Socket&&) = default;
		/// <summary>
		/// Deleted Copy Constructor.
		/// </summary>
		Socket(const Socket&) = delete;
		/// <summary>
		/// Deleted Copy Assignment Operator.
		/// </summary>
		Socket& operator=(const Socket&) = delete;

		/// <summary>
		/// Status codes that may be returned by socket functions.
		/// </summary>
		enum class Status
		{
			Done, //The socket has sent / received the data
			NotReady, //The socket is not ready to send / receive data yet
			Partial, //The socket sent a part of the data
			Disconnected, //The TCP socket has been disconnected
			Error //An unexpected error happened
		};

		/// <summary>
		/// Some special values used by sockets.
		/// </summary>
		enum
		{
			AnyPort = 0 //Special value that tells the system to pick any available port
		};

	public:
		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~Socket();

		/// <summary>
		/// Set the blocking state of the socket.<br>
		/// <br>
		/// In blocking mode, calls will not return until they have
		/// completed their task.<br>
		/// For example, a call to receive in
		/// blocking mode won't return until some data was actually
		/// received.<br>
		/// In non-blocking mode, calls will always return immediately,
		/// using the return code to signal whether there was data
		/// available or not.<br>
		/// By default, all sockets are blocking.
		/// </summary>
		/// <param name="blocking">True to set the socket as blocking, false for non-blocking.</param>
		void SetBlocking(bool blocking);

		/// <summary>
		/// Tell whether the socket is in blocking or non-blocking mode.
		/// </summary>
		/// <returns>True if the socket is blocking, false otherwise.</returns>
		bool IsBlocking() const;

	protected:
		/// <summary>
		/// Types of protocols that the socket can use.
		/// </summary>
		enum class Type
		{
			TCP, //TCP protocol
			UDP //UDP protocol
		};

		/// <summary>
		/// Default constructor.<br>
		/// <br>
		/// This constructor can only be accessed by derived classes.
		/// </summary>
		/// <param name="type">Type of the socket (TCP or UDP).</param>
		explicit Socket(Type type);

		/// <summary>
		/// Return the internal handle of the socket.<br>
		/// <br>
		/// The returned handle may be invalid if the socket
		/// was not created yet (or already destroyed).<br>
		/// This function can only be accessed by derived classes.
		/// </summary>
		/// <returns>The internal (OS-specific) handle of the socket.</returns>
		SocketHandle GetHandle() const;

		/// <summary>
		/// Create the internal representation of the socket.<br>
		/// <br>
		/// This function can only be accessed by derived classes.
		/// </summary>
		void CreateIPv4();

		/// <summary>
		/// Create the internal representation of the socket.<br>
		/// <br>
		/// This function can only be accessed by derived classes.
		/// </summary>
		void CreateIPv6();

		/// <summary>
		/// Create the internal representation of the socket
		/// from a socket handle.<br>
		/// <br>
		/// This function can only be accessed by derived classes.
		/// </summary>
		/// <param name="handle">OS-specific handle of the socket to wrap.</param>
		void Create(SocketHandle handle);

		/// <summary>
		/// Close the socket gracefully.<br>
		/// <br>
		/// This function can only be accessed by derived classes.
		/// </summary>
		void Close();

	private:
		friend class SocketSelector;

		Type m_type; //Type of the socket (TCP or UDP)
		SocketHandle m_socket; //Socket descriptor
		bool m_isBlocking; //Current blocking mode of the socket
	};
}

#endif /*_TRAP_NETWORK_SOCKET_H_*/
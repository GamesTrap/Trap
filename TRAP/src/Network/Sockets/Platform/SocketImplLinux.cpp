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

#include "TRAPPCH.h"
#include "SocketImplLinux.h"

#include <errno.h>
#include <fcntl.h>
#include <cstring>

#ifdef TRAP_PLATFORM_LINUX

sockaddr_in TRAP::INTERNAL::Network::SocketImpl::CreateAddress(uint32_t address, uint16_t port)
{
	sockaddr_in addr{};
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = htonl(address);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	return addr;
}

//-------------------------------------------------------------------------------------------------------------------//

sockaddr_in6 TRAP::INTERNAL::Network::SocketImpl::CreateAddress(const std::array<uint8_t, 16>& address, uint16_t port)
{
	sockaddr_in6 addr{};
	std::memset(&addr, 0, sizeof(addr));
	std::memcpy(addr.sin6_addr.s6_addr, address.data(), address.size());
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(port);

	return addr;
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Network::SocketHandle TRAP::INTERNAL::Network::SocketImpl::InvalidSocket()
{
	return -1;
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::Network::SocketImpl::Close(TRAP::Network::SocketHandle sock)
{
	::close(sock);
}

//-------------------------------------------------------------------------------------------------------------------//

void TRAP::INTERNAL::Network::SocketImpl::SetBlocking(TRAP::Network::SocketHandle sock, bool block)
{
	int32_t status = fcntl(sock, F_GETFL);
	if (block)
	{
		if (fcntl(sock, F_SETFL, status & ~O_NONBLOCK) == -1)
			TP_ERROR(Log::NetworkSocketUnixPrefix, "Failed to set file status flags: ", errno);
	}
	else
	{
		if (fcntl(sock, F_SETFL, status | O_NONBLOCK) == -1)
			TP_ERROR(Log::NetworkSocketPrefix, "Failed to set file status flags: ", errno);
	}
}

//-------------------------------------------------------------------------------------------------------------------//

TRAP::Network::Socket::Status TRAP::INTERNAL::Network::SocketImpl::GetErrorStatus()
{
	//The followings are sometimes equal to EWOULDBLOCK,
	//so we have to make a special case for them in order
	//to avoid having double values in the switch case
	if ((errno == EAGAIN) || (errno == EINPROGRESS))
		return TRAP::Network::Socket::Status::NotReady;

	switch (errno)
	{
	case EWOULDBLOCK:
		return TRAP::Network::Socket::Status::NotReady;

	case ECONNABORTED:
		return TRAP::Network::Socket::Status::Disconnected;

	case ECONNRESET:
		return TRAP::Network::Socket::Status::Disconnected;

	case ETIMEDOUT:
		return TRAP::Network::Socket::Status::Disconnected;

	case ENETRESET:
		return TRAP::Network::Socket::Status::Disconnected;

	case ENOTCONN:
		return TRAP::Network::Socket::Status::Disconnected;

	case EPIPE:
		return TRAP::Network::Socket::Status::Disconnected;

	default:
		return TRAP::Network::Socket::Status::Error;
	}
}

#endif
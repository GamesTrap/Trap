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

#ifndef _TRAP_NETWORK_TCPSOCKET_H_
#define _TRAP_NETWORK_TCPSOCKET_H_

#include "Socket.h"
#include "Utils/Time/TimeStep.h"

namespace TRAP::Network
{
	class TCPListener;
	class IPv4Address;
	class Packet;

	/// <summary>
	/// Specialized socket using the TCP protocol.
	/// </summary>
	class TCPSocket final : public Socket
	{
	public:
		/// <summary>
		/// Constructor.
		/// </summary>
		TCPSocket();

		/// <summary>
		/// Get the port to which the socket is bound locally.<br>
		/// <br>
		/// If the socket is not connected, this function returns 0.
		/// </summary>
		/// <returns>Port to which the socket is bound.</returns>
		uint16_t GetLocalPort() const;

		/// <summary>
		/// Get the address of the connected peer.<br>
		/// <br>
		/// If the socket is not connected, this function returns
		/// TRAP::Network::IPv4Address::None.
		/// </summary>
		/// <returns>Address of the remote peer.</returns>
		IPv4Address GetRemoteAddress() const;

		/// <summary>
		/// Get the port of the connected peer to which
		/// the socket is connected.<br>
		/// <br>
		/// If the socket is not connected, this function returns 0.
		/// </summary>
		/// <returns>Remote port to which the socket is connected.</returns>
		uint16_t GetRemotePort() const;

		/// <summary>
		/// Connect the socket to a remote peer.<br>
		/// <br>
		/// In blocking mode, this function may take a while, especially
		/// if the remote peer is not reachable.<br>
		/// The last parameter allows you to stop trying to connect after a given timeout.<br>
		/// If the socket is already connected, the connection is
		/// forcibly disconnected before attempting to connect again.
		/// </summary>
		/// <param name="remoteAddress">Address of the remote peer.</param>
		/// <param name="remotePort">Port of the remote peer.</param>
		/// <param name="timeout">Optional maximum time to wait.</param>
		/// <returns>Status code.</returns>
		Status Connect(const IPv4Address& remoteAddress, uint16_t remotePort, Utils::TimeStep timeout = Utils::TimeStep(0.0f));

		/// <summary>
		/// Disconnect the socket from its remote peer.<br>
		/// <br>
		/// This function gracefully closes the connection.<br>
		/// If the socket is not connected, this function has no effect.
		/// </summary>
		void Disconnect();

		/// <summary>
		/// Send raw data to the remote peer.<br>
		/// <br>
		/// To be able to handle partial sends over non-blocking
		/// sockets, use the Send(const void*, std::size_t, std::size_t&)
		/// overload instead.<br>
		/// This function will fail if the socket is not connected
		/// </summary>
		/// <param name="data">Pointer to the sequence of bytes to send.</param>
		/// <param name="size">Number of bytes to send.</param>
		/// <returns>Status code.</returns>
		Status Send(const void* data, std::size_t size) const;

		/// <summary>
		/// Send raw data to the remote peer.<br>
		/// <br>
		/// This function will fail if the socket is not connected
		/// </summary>
		/// <param name="data">Pointer to the sequence of bytes to send.</param>
		/// <param name="size">Number of bytes to send.</param>
		/// <param name="sent">The number of bytes sent will be written here.</param>
		/// <returns>Status code.</returns>
		Status Send(const void* data, std::size_t size, std::size_t& sent) const;

		/// <summary>
		/// Receive raw data from the remote peer.<br>
		/// <br>
		/// In blocking mode, this function will wait until some
		/// bytes are actually received.<br>
		/// This function will fail if the socket is not connected.
		/// </summary>
		/// <param name="data">Pointer to the array to fill with the received bytes.</param>
		/// <param name="size">Maximum number of bytes that can be received.</param>
		/// <param name="received">This variable is filled with the actual number of bytes received.</param>
		/// <returns>Status code.</returns>
		Status Receive(void* data, std::size_t size, std::size_t& received) const;

		/// <summary>
		/// Send a formatted packet of adata to the remote peer.<br>
		/// <br>
		/// In non-blocking mode, if this function returns TRAP::Network::Socket::Status::Partial,
		/// you must retry sending the same unmodified packet before sending
		/// anything else in order to guarantee the packet arrives at the remote
		/// peer uncorrupted.<br>
		/// This function will fail if the socket is not connected.
		/// </summary>
		/// <param name="packet">Packet to send.</param>
		/// <returns>Status code.</returns>
		Status Send(Packet& packet) const;

		/// <summary>
		/// Receive a formatted packet of data from the remote peer.<br>
		/// <br>
		/// In blocking mode, this function will wait until the whole packet
		/// has been received.<br>
		/// This function will fail if the socket is not connected.
		/// </summary>
		/// <param name="packet">Packet to fill with the received data.</param>
		/// <returns>Status code.</returns>
		Status Receive(Packet& packet);

	private:
		friend class TCPListener;

		/// <summary>
		/// Structure holding the data of a pending packet.
		/// </summary>
		struct PendingPacket
		{
			PendingPacket();

			uint32_t Size; //Data of packet size
			std::size_t SizeReceived; //Number of size bytes received so far
			std::vector<char> Data; //Data of the packet
		};

		PendingPacket m_pendingPacket; //Temporary data of the packet currently being received
	};
}

#endif /*_TRAP_NETWORK_TCPSOCKET_H_*/
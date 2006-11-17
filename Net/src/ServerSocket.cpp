//
// ServerSocket.cpp
//
// $Id: //poco/1.3/Net/src/ServerSocket.cpp#1 $
//
// Library: Net
// Package: Sockets
// Module:  ServerSocket
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/ServerSocketImpl.h"
#include "Poco/Exception.h"


using Poco::InvalidArgumentException;


namespace Poco {
namespace Net {


ServerSocket::ServerSocket(): Socket(new ServerSocketImpl)
{
}


ServerSocket::ServerSocket(const Socket& socket): Socket(socket)
{
	if (!dynamic_cast<ServerSocketImpl*>(impl()))
		throw InvalidArgumentException("Cannot assign incompatible socket");
}


ServerSocket::ServerSocket(const SocketAddress& address, int backlog): Socket(new ServerSocketImpl)
{
	impl()->bind(address, true);
	impl()->listen(backlog);
}


ServerSocket::ServerSocket(Poco::UInt16 port, int backlog): Socket(new ServerSocketImpl)
{
	IPAddress wildcardAddr;
	SocketAddress address(wildcardAddr, port);
	impl()->bind(address, true);
	impl()->listen(backlog);
}


ServerSocket::ServerSocket(SocketImpl* pImpl, bool ignore): Socket(pImpl)
{
}


ServerSocket::~ServerSocket()
{
}


ServerSocket& ServerSocket::operator = (const Socket& socket)
{
	if (dynamic_cast<ServerSocketImpl*>(socket.impl()))
		Socket::operator = (socket);
	else
		throw InvalidArgumentException("Cannot assign incompatible socket");
	return *this;
}


void ServerSocket::bind(const SocketAddress& address, bool reuseAddress)
{
	impl()->bind(address, reuseAddress);
}


void ServerSocket::bind(Poco::UInt16 port, bool reuseAddress)
{
	IPAddress wildcardAddr;
	SocketAddress address(wildcardAddr, port);
	impl()->bind(address, reuseAddress);
}

	
void ServerSocket::listen(int backlog)
{
	impl()->listen(backlog);
}


StreamSocket ServerSocket::acceptConnection(SocketAddress& clientAddr)
{
	return StreamSocket(impl()->acceptConnection(clientAddr));
}


StreamSocket ServerSocket::acceptConnection()
{
	SocketAddress clientAddr;
	return StreamSocket(impl()->acceptConnection(clientAddr));
}


} } // namespace Poco::Net

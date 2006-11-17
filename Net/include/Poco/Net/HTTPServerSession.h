//
// HTTPServerSession.h
//
// $Id: //poco/1.3/Net/include/Poco/Net/HTTPServerSession.h#1 $
//
// Library: Net
// Package: HTTPServer
// Module:  HTTPServerSession
//
// Definition of the HTTPServerSession class.
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


#ifndef Net_HTTPServerSession_INCLUDED
#define Net_HTTPServerSession_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/HTTPSession.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Timespan.h"


namespace Poco {
namespace Net {


class HTTPServerParams;


class Net_API HTTPServerSession: public HTTPSession
	/// This class handles the server side of a
	/// HTTP session. It is used internally by
	/// HTTPServer.
{
public:
	HTTPServerSession(const StreamSocket& socket, HTTPServerParams* pParams);
		/// Creates the HTTPServerSession.

	virtual ~HTTPServerSession();
		/// Destroys the HTTPServerSession.
				
	bool hasMoreRequests();
		/// Returns true if there are requests available.
		
	SocketAddress clientAddress();
		/// Returns the client's address.
		
	SocketAddress serverAddress();
		/// Returns the server's address.
		
private:
	bool           _firstRequest;
	Poco::Timespan _keepAliveTimeout;
	int            _maxKeepAliveRequests;
};


} } // namespace Poco::Net


#endif // Net_HTTPServerSession_INCLUDED

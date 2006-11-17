//
// RemoteSyslogChannel.cpp
//
// $Id: //poco/1.3/Net/src/RemoteSyslogChannel.cpp#1 $
//
// Library: Net
// Package: Logging
// Module:  RemoteSyslogChannel
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
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


#include "Poco/Net/RemoteSyslogChannel.h"
#include "Poco/Message.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/DNS.h"
#include "Poco/LoggingFactory.h"
#include "Poco/Instantiator.h"
#include "Poco/String.h"


namespace Poco {
namespace Net {


const std::string RemoteSyslogChannel::PROP_NAME("name");
const std::string RemoteSyslogChannel::PROP_FACILITY("facility");
const std::string RemoteSyslogChannel::PROP_FORMAT("format");
const std::string RemoteSyslogChannel::PROP_LOGHOST("loghost");
const std::string RemoteSyslogChannel::PROP_HOST("host");


RemoteSyslogChannel::RemoteSyslogChannel():
	_logHost("localhost"),
	_name("-"),
	_facility(SYSLOG_USER),
	_bsdFormat(false),
	_open(false)
{
}

		
RemoteSyslogChannel::RemoteSyslogChannel(const std::string& address, const std::string& name, int facility, bool bsdFormat):
	_logHost(address),
	_name(name),
	_facility(facility),
	_bsdFormat(bsdFormat),
	_open(false)
{
	if (_name.empty()) _name = "-";
}


RemoteSyslogChannel::~RemoteSyslogChannel()
{
	close();
}


void RemoteSyslogChannel::open()
{
	if (_open) return;
	
	SocketAddress sa;
	if (_logHost.find(':') != std::string::npos)
		sa = SocketAddress(_logHost);
	else
		sa = SocketAddress(_logHost, SYSLOG_PORT);

	_socket.connect(sa);
	if (_host.empty())
	{
		try
		{
			_host = DNS::thisHost().name();
		}
		catch (Poco::Exception&)
		{
			_host = _socket.address().host().toString();
		}
	}
}

	
void RemoteSyslogChannel::close()
{
	if (_open)
	{
		_socket.close();
		_open = false;
	}
}

	
void RemoteSyslogChannel::log(const Message& msg)
{
	if (!_open) open();

	std::string m;
	m.reserve(1024);
	m += '<';
	m += Poco::NumberFormatter::format(getPrio(msg) + _facility);
	m += '>';
	if (_bsdFormat)
	{
		m += Poco::DateTimeFormatter::format(msg.getTime(), "%w %f %H:%M:%S");
		m += ' ';
		m += _host;
	}
	else
	{
		m += "1 "; // version
		m += Poco::DateTimeFormatter::format(msg.getTime(), "%Y-%m-%dT%H:%M:%S.%i%z");
		m += ' ';
		m += _host;
		m += ' ';
		m += _name;
		m += ' ';
		m += Poco::NumberFormatter::format(msg.getPid());
		m += ' ';
		m += msg.getSource();
	}
	m += ' ';
	m += msg.getText();

	_socket.sendBytes(m.data(), (int) m.size());
}

	
void RemoteSyslogChannel::setProperty(const std::string& name, const std::string& value)
{
	if (name == PROP_NAME)
	{
		_name = value;
		if (_name.empty()) _name = "-";
	}
	else if (name == PROP_FACILITY)
	{
		std::string facility;
		if (Poco::icompare(value, 4, "LOG_") == 0)
			facility = Poco::toUpper(value.substr(4));
		else if (Poco::icompare(value, 4, "SYSLOG_") == 0)
			facility = Poco::toUpper(value.substr(7));
		else
			facility = Poco::toUpper(value);
		
		if (facility == "KERN")
			_facility = SYSLOG_KERN;
		else if (facility == "USER")
			_facility = SYSLOG_USER;
		else if (facility == "MAIL")
			_facility = SYSLOG_MAIL;
		else if (facility == "DAEMON")
			_facility = SYSLOG_DAEMON;
		else if (facility == "AUTH")
			_facility = SYSLOG_AUTH;
		else if (facility == "AUTHPRIV")
			_facility = SYSLOG_AUTHPRIV;
		else if (facility == "SYSLOG")
			_facility = SYSLOG_SYSLOG;
		else if (facility == "LPR")
			_facility = SYSLOG_LPR;
		else if (facility == "NEWS")
			_facility = SYSLOG_NEWS;
		else if (facility == "UUCP")
			_facility = SYSLOG_UUCP;
		else if (facility == "CRON")
			_facility = SYSLOG_CRON;
		else if (facility == "FTP")
			_facility = SYSLOG_FTP;
		else if (facility == "NTP")
			_facility = SYSLOG_NTP;
		else if (facility == "LOGAUDIT")
			_facility = SYSLOG_LOGAUDIT;
		else if (facility == "LOGALERT")
			_facility = SYSLOG_LOGALERT;
		else if (facility == "CLOCK")
			_facility = SYSLOG_CLOCK;
		else if (facility == "LOCAL0")
			_facility = SYSLOG_LOCAL0;
		else if (facility == "LOCAL1")
			_facility = SYSLOG_LOCAL1;
		else if (facility == "LOCAL2")
			_facility = SYSLOG_LOCAL2;
		else if (facility == "LOCAL3")
			_facility = SYSLOG_LOCAL3;
		else if (facility == "LOCAL4")
			_facility = SYSLOG_LOCAL4;
		else if (facility == "LOCAL5")
			_facility = SYSLOG_LOCAL5;
		else if (facility == "LOCAL6")
			_facility = SYSLOG_LOCAL6;
		else if (facility == "LOCAL7")
			_facility = SYSLOG_LOCAL7;
	}
	else if (name == PROP_LOGHOST)
	{
		_logHost = value;
	}
	else if (name == PROP_HOST)
	{
		_host = value;
	}
	else if (name == PROP_FORMAT)
	{
		_bsdFormat = (value == "bsd");
	}
	else
	{
		Channel::setProperty(name, value);
	}
}

	
std::string RemoteSyslogChannel::getProperty(const std::string& name) const
{
	if (name == PROP_NAME)
	{
		if (_name != "-")
			return _name;
		else
			return "";
	}
	else if (name == PROP_FACILITY)
	{
		if (_facility == SYSLOG_KERN)
			return "KERN";
		else if (_facility == SYSLOG_USER)
			return "USER";
		else if (_facility == SYSLOG_MAIL)
			return "MAIL";
		else if (_facility == SYSLOG_DAEMON)
			return "DAEMON";
		else if (_facility == SYSLOG_AUTH)
			return "AUTH";
		else if (_facility == SYSLOG_AUTHPRIV)
			return "AUTHPRIV";
		else if (_facility == SYSLOG_SYSLOG)
			return "SYSLOG";
		else if (_facility == SYSLOG_LPR)
			return "LPR";
		else if (_facility == SYSLOG_NEWS)
			return "NEWS";
		else if (_facility == SYSLOG_UUCP)
			return "UUCP";
		else if (_facility == SYSLOG_CRON)
			return "CRON";
		else if (_facility == SYSLOG_FTP)
			return "FTP";
		else if (_facility == SYSLOG_NTP)
			return "NTP";
		else if (_facility == SYSLOG_LOGAUDIT)
			return "LOGAUDIT";
		else if (_facility == SYSLOG_LOGALERT)
			return "LOGALERT";
		else if (_facility == SYSLOG_CLOCK)
			return "CLOCK";
		else if (_facility == SYSLOG_LOCAL0)
			return "LOCAL0";
		else if (_facility == SYSLOG_LOCAL1)
			return "LOCAL1";
		else if (_facility == SYSLOG_LOCAL2)
			return "LOCAL2";
		else if (_facility == SYSLOG_LOCAL3)
			return "LOCAL3";
		else if (_facility == SYSLOG_LOCAL4)
			return "LOCAL4";
		else if (_facility == SYSLOG_LOCAL5)
			return "LOCAL5";
		else if (_facility == SYSLOG_LOCAL6)
			return "LOCAL6";
		else if (_facility == SYSLOG_LOCAL7)
			return "LOCAL7";
		else
			return "";
	}
	else if (name == PROP_LOGHOST)
	{
		return _logHost;
	}
	else if (name == PROP_HOST)
	{
		return _host;
	}
	else if (name == PROP_FORMAT)
	{
		return _bsdFormat ? "bsd" : "new";
	}
	else
	{
		return Channel::getProperty(name);
	}
}


int RemoteSyslogChannel::getPrio(const Message& msg)
{
	switch (msg.getPriority())
	{
	case Message::PRIO_TRACE:
	case Message::PRIO_DEBUG:
		return SYSLOG_DEBUG;
	case Message::PRIO_INFORMATION:
		return SYSLOG_INFORMATIONAL;
	case Message::PRIO_NOTICE:
		return SYSLOG_NOTICE;
	case Message::PRIO_WARNING:
		return SYSLOG_WARNING;
	case Message::PRIO_ERROR:
		return SYSLOG_ERROR;
	case Message::PRIO_CRITICAL:
		return SYSLOG_CRITICAL;
	case Message::PRIO_FATAL:
		return SYSLOG_ALERT;
	default:
		return 0;
	}
}


void RemoteSyslogChannel::registerChannel()
{
	Poco::LoggingFactory::defaultFactory().registerChannelClass("RemoteSyslogChannel", new Poco::Instantiator<RemoteSyslogChannel, Poco::Channel>);
}


} } // namespace Poco::Net

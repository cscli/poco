//
// FilePartSource.cpp
//
// $Id: //poco/1.3/Net/src/FilePartSource.cpp#1 $
//
// Library: Net
// Package: Messages
// Module:  FilePartSource
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


#include "Poco/Net/FilePartSource.h"
#include "Poco/Path.h"
#include "Poco/Exception.h"


using Poco::Path;
using Poco::OpenFileException;


namespace Poco {
namespace Net {


FilePartSource::FilePartSource(const std::string& path):
	_istr(path.c_str(), std::ios::in | std::ios::binary)
{
	Path p(path);
	_filename = p.getFileName();
	if (!_istr.good())
		throw OpenFileException(path);
}


FilePartSource::FilePartSource(const std::string& path, const std::string& mediaType):
	PartSource(mediaType),
	_istr(path.c_str(), std::ios::in | std::ios::binary)
{
	Path p(path);
	_filename = p.getFileName();
	if (!_istr.good())
		throw OpenFileException(path);
}


FilePartSource::~FilePartSource()
{
}


std::istream& FilePartSource::stream()
{
	return _istr;
}


const std::string& FilePartSource::filename()
{
	return _filename;
}


} } // namespace Poco::Net

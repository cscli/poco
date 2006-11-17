//
// FilePartSource.h
//
// $Id: //poco/1.3/Net/include/Poco/Net/FilePartSource.h#1 $
//
// Library: Net
// Package: Messages
// Module:  FilePartSource
//
// Definition of the FilePartSource class.
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


#ifndef Net_FilePartSource_INCLUDED
#define Net_FilePartSource_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/PartSource.h"
#include <fstream>


namespace Poco {
namespace Net {


class Net_API FilePartSource: public PartSource
	/// An implementation of PartSource for
	/// plain files.
{
public:
	FilePartSource(const std::string& path);
		/// Creates the FilePartSource for the given path.
		///
		/// The MIME type is set to application/octet-stream.
		///
		/// Throws an OpenFileException if the file cannot be opened.
	
	FilePartSource(const std::string& path, const std::string& mediaType);
		/// Creates the FilePartSource for the given
		/// path and MIME type.
		///
		/// Throws an OpenFileException if the file cannot be opened.

	~FilePartSource();
		/// Destroys the FilePartSource.

	std::istream& stream();
		/// Returns a file input stream for the given file.
		
	const std::string& filename();
		/// Returns the filename portion of the path.

private:
	std::ifstream _istr;
	std::string   _filename;
};


} } // namespace Poco::Net


#endif // Net_FilePartSource_INCLUDED

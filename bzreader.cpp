/*
 * AikSaurus - An open source thesaurus library
 * Copyright (C) 2001 by Jared Davis
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
 * 02111-1307, USA.
 *
 */

#include "bzreader.h"
#include <cstdio>
#include <bzlib.h>

#ifndef NDEBUG
	#include <iostream>
#endif

using namespace std;


class BZReader_Impl
{
	private:

		static unsigned int s_readBufferSize;
		
		static const char* s_noError;
		static const char* s_fileOpenError;
		static const char* s_failedBZReadOpen;
		static const char* s_noStreamOpen;
		static const char* s_badRead;
		
		const char* d_errorString;
		int d_error;
		
		char* d_readBuffer_ptr;
		unsigned int d_readBuffer_pos;
		
		FILE* d_fileHandle;
		BZFILE *bzin;

		bool nextWord(string& str);
		
	public:
		BZReader_Impl(const string& path);
		~BZReader_Impl();
	
		inline
		bool operator>>(string& str);

		inline
		const char* error() const;

		#ifndef NDEBUG
		void debug();	
		#endif // NDEBUG
};


// s_readBufferSize
//   This controls how much data is to be read from the file at a time, 
//   in bytes.  It is an arbitrary constant and is most likely not optimal.
unsigned int BZReader_Impl::s_readBufferSize = 1024;

const char* BZReader_Impl::s_noError = 
	"";

const char* BZReader_Impl::s_fileOpenError =
	"BZReader_Impl: There was an error opening the specified file for reading.";

const char* BZReader_Impl::s_failedBZReadOpen = 
	"BZReader_Impl: File opened successfully, but BZReadOpen fails.";

const char* BZReader_Impl::s_noStreamOpen =
	"BZReader_Impl: Read attempted, but the input stream is not open.";

const char* BZReader_Impl::s_badRead = 
	"BZReader_Impl: An error occured while reading from the stream.";
	
	

#ifndef NDEBUG

// 
// BZReader_Impl::debug()
//   Simply prints some debugging information about the stream.
//   You will want to go ahead and compile with NDEBUG defined to 
//   get rid of this.
//   
void BZReader_Impl::debug()
{
	cout << "BZReader_Impl::debug() Information: " << endl;
	cout << "  Current error: " << error() << endl;
	cout << "  Current d_error value: " << d_error << endl;
	cout << "  Current d_error interpretation: " << BZ2_bzerror(bzin, &d_error) << endl;
	cout << "  d_fileHandle is null? " << (d_fileHandle == NULL) << endl;
	cout << "  bzin is null? " << (bzin == NULL) << endl;
	cout << "End of BZReader_Impl::debug() Information." << endl;
}

#endif // NDEBUG


BZReader_Impl::BZReader_Impl(const string& path)
: d_errorString(s_noError),
  d_error(BZ_OK),
  d_readBuffer_ptr(new char[s_readBufferSize]), 
  d_readBuffer_pos(s_readBufferSize), 
  d_fileHandle(NULL),
  bzin(NULL)
{
	d_fileHandle = fopen(path.c_str(), "r");

	if (!d_fileHandle)
	{
		d_errorString = s_fileOpenError;
		return;
	}
	
	bzin = BZ2_bzReadOpen(&d_error, d_fileHandle, 0, 0, NULL, 0);

	if (d_error != BZ_OK)
	{
		d_errorString = s_failedBZReadOpen;
		return;
	}
}


// 
// BZReader_Impl::~BZReader_Impl()
//   We must free the read buffer, and possibly close the bz input
//   stream.  We also need to close the file descriptor itself.
// 
BZReader_Impl::~BZReader_Impl()
{
	delete d_readBuffer_ptr;
	
	if (bzin)
	{
		BZ2_bzReadClose(&d_error, bzin);
	}
	
	if (d_fileHandle)
	{
		fclose(d_fileHandle);
	}
}


//
// BZReader_Impl::nextWord
//   Recursively appends characters from our buffer into a string,
//   stopping as soon as a space is encountered.  Might have to read
//   in a new buffer if there's no space before the end of the buffer.
//   
bool BZReader_Impl::nextWord(string& str)
{
	for(unsigned int i = d_readBuffer_pos; i < s_readBufferSize; ++i)
	{
		if (isspace(d_readBuffer_ptr[i]))
		{
			d_readBuffer_pos = i + 1;
			d_errorString = s_noError;
			return true;
		}
		
		else
		{
			str += d_readBuffer_ptr[i];
		}
	}

	// if we get this far, we've hit the end of the buffer.
	// we need to read some more data.

	if (!bzin)
	{
		d_errorString = s_noStreamOpen;
		return false;
	}

	BZ2_bzRead(&d_error, bzin, d_readBuffer_ptr, s_readBufferSize);
		
	if (d_error == BZ_STREAM_END)
	{
		// end of stream encountered normally.
		// constructor can destroy it for us.
		d_errorString = s_noError;
		return false;
	}
	
	
	else if (d_error != BZ_OK)
	{
		// some sort of error occured.
		// let's close the stream and return false from
		// now on.
		d_errorString = s_badRead;
		BZ2_bzReadClose(&d_error, bzin);
		bzin = NULL;
		return false;
	}
	
	// reset the buffer position to 0 since we've just read in a new
	// buffer, and recursively continue looking for spaces.
	d_readBuffer_pos = 0;
	return nextWord(str);
}


// 
// BZReader_Impl::operator>>()
// 
//   The extraction operator is based on nextWord, but nextWord may
//   have to recurse if no space is found before the end of the buffer.
//   so, we set up nextWord to just append to a string, and then for
//   the actual read we just initialize the string to null as follows:
//   
bool BZReader_Impl::operator>>(string& str)
{
	str = "";
	return nextWord(str);
}


//
// BZReader_Impl::error()
//   Returns a string describing error status. 
//   
inline
const char* BZReader_Impl::error() const
{
	return d_errorString;
}






//
// BZReader Class Implementation
// 
//   The BZReader class itself just wraps around the implementation
//   class.  This provides good insulation and means that we can keep
//   nearly all of our #include statements out of the header file, 
//   which is good practice.
//
//   The implementation of this class is now trivial since the 
//   implementation class does all the work.
//

BZReader::BZReader(const std::string& str)
: d_impl_ptr(new BZReader_Impl(str))
{
	
}

BZReader::~BZReader()
{
	delete d_impl_ptr;
}

bool BZReader::operator>>(std::string& str)
{
	return (*d_impl_ptr) >> str;
}

const char* BZReader::error() const
{
	return d_impl_ptr->error();
}

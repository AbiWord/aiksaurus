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

#include "AikString.h"
#include <new>
using namespace std;

//
// Null String
// -----------
//   This is here so that in the unlikely event that we run out
//   of memory, we can set the buffer to a null string and hence
//   not terminate the program.
//   
char* AikString::s_nullString = "";


//
// stringLength
// ------------
//   Returns length of a string, except for the null terminator.
//   For example, stringLength("foo") = 3.
//
//   Not safe to use on NULL.
//
inline 
static unsigned int stringLength(const char* str)
{
	register unsigned int i = 0;
	while(str[i] != '\0') ++i;
	return i;
}


//
// stringCopy
// ----------
//   Copies the contents of src into target.
//   The null terminator is included in the copy.
//   Target MUST BE at least large enough to hold source.
//   It can also be bigger, but this will result in waste.
//
inline 
static void stringCopy(const char* src, char* target)
{
	register int i = 0;
		
	do
	{
		target[i] = src[i];
	}
		
	while(src[i++] != '\0');
}

// 
// AikString::init
// ---------------
//   This initializes our buffer, and makes it a copy of target.
//   Before using this function, ensure that d_size is set to the
//   correct lenght to hold target.
// 
inline 
void AikString::init(const char* source)
{
	d_buf_ptr = new(nothrow) char[d_size+1];

	d_valid = d_buf_ptr;

	if (d_valid)
	{
		stringCopy(source, d_buf_ptr);
	}

	else
	{
		d_size = 0;
		d_buf_ptr = s_nullString;
	}
}


//
// AikString::destruct
// -------------------
//   Destroy the buffer we created, if it needs to be destroyed.
//   
inline
void AikString::destruct()
{
	if (d_buf_ptr != s_nullString)
	{
		delete d_buf_ptr;
	}
}


AikString::AikString(const char* rhs)
{
	if (rhs == 0)
	{
		d_size = 0;
		d_buf_ptr = s_nullString;
		d_valid = true;
	}
			
	else
	{
		d_size = stringLength(rhs);
		init(rhs);
	}
}


AikString::AikString(const AikString& rhs)
{
	d_size = rhs.size();
	init(rhs.c_str());
}


const AikString& AikString::operator=(const AikString& rhs)
{
	destruct();
	d_size = rhs.size();
	init(rhs.c_str());
	return (*this);
}


const AikString& AikString::operator=(const char* rhs)
{
	destruct();	
	d_size = stringLength(rhs);
	init(rhs);
	return (*this);
}


static 
char* stringConcatenate(
	const char* lhs, 
	const char* rhs, 
	unsigned int lhs_size, 
	unsigned int rhs_size, 
	unsigned int& ret_size
)
{
	ret_size = rhs_size + lhs_size;
	
	char* ret = new(nothrow) char[ret_size + 1];

	if (!ret)
		return 0;

	register unsigned int i = 0;
	
	while(i < lhs_size)
	{
		ret[i] = lhs[i];
		++i;
	}
	
	while(i < ret_size)
	{
		ret[i] = rhs[i - lhs_size];
		++i;
	}

	ret[i] = '\0';

	return ret;
}





const AikString& AikString::operator+=(const char* rhs)
{
	if (rhs == 0)
		return (*this);

	unsigned int new_size;
	char* cat = stringConcatenate(
		d_buf_ptr,
		rhs,
		d_size,
		stringLength(rhs),
		new_size
	);
	
	destruct();
	
	if (cat)
	{
		d_buf_ptr = cat;
		d_size = new_size;
		d_valid = true;
	}
	
	else  // alloc failed.
	{
		d_size = 0;
		d_buf_ptr = s_nullString;
		d_valid = false;
	}

	return (*this);
}

const AikString& AikString::operator+=(const AikString& rhs)
{
	if (rhs.size() == 0)
		return (*this);
	
	unsigned int new_size;
	char* cat = stringConcatenate(
		d_buf_ptr,
		rhs.c_str(),
		d_size,
		rhs.size(),
		new_size
	);

	destruct();

	if (cat)
	{
		d_buf_ptr = cat;
		d_size = new_size;
		d_valid = true;
	}
	
	else
	{
		d_size = 0;
		d_buf_ptr = s_nullString;
		d_valid = false;
	}

	return (*this);
}


AikString::~AikString()
{
	destruct();
}


bool operator==(const AikString& lhs, const AikString& rhs)
{
	if (lhs.size() != rhs.size())
		return false;

	const char* lcstr = lhs.c_str();
	const char* rcstr = rhs.c_str();
	const unsigned int size = lhs.size();
	
	for(register unsigned int i = 0;i < size;++i)
	{
		if (lcstr[i] != rcstr[i])
			return false;
	}
	
	return true;
}

bool operator!=(const AikString& lhs, const AikString& rhs)
{
	return !(lhs == rhs);
}

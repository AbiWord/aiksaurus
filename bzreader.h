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

#ifndef INCLUDED_BZREADER_H
#define INCLUDED_BZREADER_H

/* 
 * BZReader Class
 * --------------
 *   This basically just simplifies the reading of .bz2 text files
 *   that are used by the thesaurus.  It gives us a nice wrapper 
 *   around the compression library so we don't have to mess with 
 *   it in the middle of our thesaurus code.
 */

#include <string>

class BZReader_Impl;
class BZReader
{
	private:
		BZReader_Impl *d_impl_ptr;
	
	public:
		BZReader(const std::string& path);
		~BZReader();

		bool operator>>(std::string& str);

		const char* error() const;
};

#endif // INCLUDED_BZREADER_H


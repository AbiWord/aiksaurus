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

#ifndef INCLUDED_JARED_GPL_AIKSTRING_H
#define INCLUDED_JARED_GPL_AIKSTRING_H

class AikString
{
	private:
	
		static char* s_nullString;
		
		bool d_valid;
		char* d_buf_ptr;
		
		unsigned int d_size;
	
		void init(const char* src);
		void destruct();
		
	public:	

	// Creation ---
		
		explicit AikString(const char* rhs = 0);
		explicit AikString(const char* rhs, unsigned int size);
		AikString(const AikString& rhs);
		~AikString();

		
	// Inspection ---
	
		unsigned int size() const
		{
			return d_size;
		}	
		
		const char* c_str() const
		{
			return d_buf_ptr;
		}

		bool valid() const
		{
			return d_valid;
		}

		
	// Manipulation ---
	
		const AikString& operator=(const char* rhs);
		const AikString& operator=(const AikString& rhs);
		
		const AikString& operator+=(const char* rhs);
		const AikString& operator+=(const AikString& rhs);
		
		void replaceAll(char a, char b)
		{
			for(register unsigned int i = 0;i < size();++i)
			{
				if (d_buf_ptr[i] == a)
					d_buf_ptr[i] = b;
			}
		}
};

bool operator==(const AikString& lhs, const AikString& rhs);
bool operator!=(const AikString& lhs, const AikString& rhs);

#endif // INCLUDED_JARED_GPL_AIKSTRING_H

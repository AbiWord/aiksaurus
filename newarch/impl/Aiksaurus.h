/*
 * Aiksaurus - An open source thesaurus library
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

#ifndef INCLUDED_GPL_JARED_AIKSAURUS_H
#define INCLUDED_GPL_JARED_AIKSAURUS_H

class AiksaurusImpl;
class Aiksaurus
{
	private:

		AiksaurusImpl *d_impl_ptr;
		
		// prevent copying or assignment, since this is 
		// a large object to create and destroy.
		Aiksaurus(const AikSaurus& rhs);
		const Aiksaurus& operator=(const AikSaurus& rhs);
		
	public:
		
		AikSaurus();
		~AikSaurus();
		
		// call 'word' to figure out what word is current.
		const char* word() const;
		
		// call 'find' to set up which word you want 
		// the results from. Returns true if the word is
		// found, false otherwise.
		bool find(const char* word);
	
        // call 'next' repeatedly to return one synonym
        // at a time, until it returns empty string.  
        // you should not delete the string:  the next 
        // call to 'next' will overwrite the string.
        // 'meaning' is an integer indicating which
        // meaning this synonym belongs to.  
        const char* next(int& meaning);
        
        // call 'label' to return the label for a 
        // meaning id.  NOT IMPLEMENTED YET.
        // at present, this will just return
        // 'null'.
        const char* label(int meaning); 
		
		// call 'similar' repeatdly to return one 
		// "nearby word" at a time.  these are not 
		// synonyms: they are known words that are 
		// alphabetically near the searched-for word.
		const char* similar();
		
		// call 'error' to find out if something went 
		// wrong.  will be empty if no problems.  you
		// do not have to delete this string, it is 
		// managed automatically.
		const char* error() const;

};

#endif // INCLUDED_GPL_JARED_AIKSAURUS_H

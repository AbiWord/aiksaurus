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

#ifndef INCLUDED_AIKSAURUS_H
#define INCLUDED_AIKSAURUS_H

namespace AiksaurusImpl
{
    class ThesaurusImpl;
    class Aiksaurus
    {
	    private:
           
    		// Prevent copying and assignment
    		Aiksaurus(const Aiksaurus& rhs);
	    	Aiksaurus& operator=(const Aiksaurus& rhs);
            
            ThesaurusImpl *d_impl_ptr;
            const char* d_error; 
            
        public:
       		
            Aiksaurus() throw();
	    	~Aiksaurus() throw();
            
    		// word(): returns current word that is being
            // searched for.  You should not try to delete 
            // this string.
	    	const char* word() const throw();
    		
            // error(): empty string if no problems encountered.
            // otherwise, a human-suitable description of the 
            // problem will be presented.
            //  + Do not try to delete this string.
	    	const char* error() const throw();
           
            
    		// find(): perform a search for a new word.  
            // returns *true* if word is known, *false* otherwise.
    		bool find(const char* word) throw();
            
            // next(): return synonyms for the word.
            //  + Do not try to delete this string.
            //  + *meaning* will change as new meanings are 
            //    encountered
            //  + the first two words of any meaning are 
            //    titles for that meaning.
            //  + returns an empty string when out of synonyms.
            const char* next(int& meaning) throw();
            
    		// similar(): repeatdly to return one "nearby word" 
            // at a time.  these are not synonyms: they are known
            // words that are alphabetically near the 
            // searched-for word.
	    	const char* similar() throw();
    };
}

typedef AiksaurusImpl::Aiksaurus Aiksaurus;

#endif // INCLUDED_AIKSAURUS_H

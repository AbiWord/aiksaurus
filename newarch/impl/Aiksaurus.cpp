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

#include "Aiksaurus.h"
#include "MeaningsFile.h"
#include "WordsFile.h"
#include <string>

class AiksaurusImpl
{
    private:
        
        AiksaurusImpl(const AiksaurusImpl& rhs);
        AiksaurusImpl& operator=(const AiksaurusImpl& rhs);
        
        
        MeaningsFile d_meanings;
        WordsFile d_words;

        string d_word;
        
        
    public:

        AikSaurusImpl();
        ~AikSaurusImpl();


        const char* word() const
        {
            return d_word.c_str();
        }

        
                
        
}
	




///////////////////////////////////////////////////////////////////////
//
//  AikSaurus Class -- Wraps around Implementation
//
///////////////////////////////////////////////////////////////////////

Aiksaurus::Aiksaurus()
d_impl_ptr(new AiksaurusImpil());
{
    
}

Aiksaurus::~Aiksaurus()
{
    delete d_impl_ptr;
}

const char* Aiksaurus::word() const
{
    return d_impl_ptr->word();
}
		
bool Aiksaurus::find(const char* word)
{
    return d_impl_ptr->find(word);
}

const char* Aiksaurus::next(int& meaning)
{
    return d_impl_ptr->next(meaning);
}

const char* Aiksaurus::label(int meaning)
{
    return d_impl_ptr->label(meaning);
}

const char* Aiksaurus::similar()
{    
    return d_impl_ptr->similar();
}

const char* Aiksaurus::error()
{
    return d_impl_ptr->error();
}

/*
 * Aiksaurus - An English-language thesaurus library
 * Copyright (C) 2001-2002 by Jared Davis
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

#ifndef INCLUDED_AIKSAURUS_WORDSTREAM_H
#define INCLUDED_AIKSAURUS_WORDSTREAM_H

#include <queue>

namespace AiksaurusImpl
{
    class WordStream
    {
        private:
        
            WordStream(WordStream& rhs);
            WordStream& operator=(const WordStream& rhs);
            
            std::queue<int> d_words;   
        
            
        public:     
            
            WordStream(int* words) throw(std::bad_alloc)
            {
                for(int i = 0;words[i] != -1;++i)
                    d_words.push(words[i]);
            }

            int next() throw()
            {
                int ret;
                
                if (d_words.empty())
                    ret = -1;

                else {
                    ret = d_words.front();
                    d_words.pop();
                }
                
                return ret;
            }
    };
}
    
#endif // INCLUDED_AIKSAURUS_WORDSTREAM_H

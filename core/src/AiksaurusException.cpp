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

#include "AiksaurusException.h"     // Header we're implementing.
#include "config.h"                 // For AIK_DATA_DIR define.
#include <cassert>                   
#include <string>                   // for std::string
#include <cstring>                  // for strcpy
#include <new>                      // for std::bad_alloc
using namespace std;

#if defined WIN32
	extern std::string aik_data_dir;
#endif

namespace AiksaurusImpl
{
    const char* AiksaurusException::MemoryError = 
        "Error: Cannot Allocate Memory\n"
        "No memory was available for the Thesaurus.  You  \n"
        "could try closing some other programs to make more \n"
        "memory available.\n";

    
    AiksaurusException::AiksaurusException(Code code) throw()
    {
        assert(
            (code == CANNOT_OPEN_MEANINGS_FILE) ||
            (code == CORRUPT_MEANINGS_FILE) ||
            (code == CANNOT_OPEN_WORDS_FILE) ||
            (code == CORRUPT_WORDS_FILE) ||
            (code == CANNOT_ALLOCATE_MEMORY)
        );

        if (code == CANNOT_ALLOCATE_MEMORY)
        {
            d_description = MemoryError;
            return;
        }
        
        try 
        {    
            string err;

            switch(code)
            {
                case CANNOT_OPEN_MEANINGS_FILE:
                    err = "Error: Cannot Open Meanings File\n"
                          "There has been a problem opening the file:\n   ";
                    err += AIK_DATA_DIR;
                    err += "meanings.dat\n\n"
                           "This most likely indicates that the file has been \n"
                           "moved or deleted.  If you cannot find the file, you \n"
                           "can download a new copy from: \n"
                           "   http://www.aiksaurus.com/_support/015/meanings.dat\n";
                    break;

                    
                case CORRUPT_MEANINGS_FILE:
                    err = "Error: Corrupt Meanings File\n"
                          "There has been a problem reading the file:\n   ";
                    err += AIK_DATA_DIR;
                    err += "meanings.dat\n\n"
                           "The file exists, but was not read correctly.  Either \n"
                           "the file has become corrupt or this is a bug. \n\n"
                           "Please download a new copy of the file from: \n"
                           "   http://www.aiksaurus.com/_support/015/meanings.dat\n\n"
                           "If this does not fix the problem, please contact \n"
                           "   jared@aiksaurus.com\n";
                    break;
        
                    
                case CANNOT_OPEN_WORDS_FILE:
                    err = "Error: Cannot Open Words File\n"
                          "There has been a problem opening the file:\n   ";
                    err += AIK_DATA_DIR;
                    err += "words.dat\n\n"
                           "This most likely indicates that the file has been \n"
                           "moved or deleted.  If you cannot find the file, you \n"
                           "can download a new copy from: \n"
                           "   http://www.aiksaurus.com/_support/015/words.dat\n";
                    break;
    
                    
                case CORRUPT_WORDS_FILE: 
                    err = "Error: Corrupt Words File\n"
                          "There has been a problem reading the file:\n   ";
                    err += AIK_DATA_DIR;
                    err += "words.dat\n\n"        
                           "The file exists, but was not read correctly.  Either \n"
                           "the file has become corrupt or this is a bug. \n\n"
                           "Please download a new copy of the file from: \n"
                           "   http://www.aiksaurus.com/_support/015/words.dat\n\n"
                           "If this does not fix the problem, please contact \n"
                           "   jared@aiksaurus.com\n";
                    break;

                default: 
                    // shut up the compiler about not handling CANNOT_ALLOCATE_MEMORY
                    // in the switch statement.  We handled it before.
                    break;
                    
            }
            
            d_description = new char[err.size() + 1];
            strcpy(const_cast<char*>(d_description), err.c_str());
        }
        
        catch(std::bad_alloc)
        {
            d_description = MemoryError;
        }
    }

    
    AiksaurusException::~AiksaurusException() throw()
    {
        if( d_description != MemoryError )
		{
#if !defined WIN32
			delete[] d_description;
#endif
		}
    }


    const char* 
    AiksaurusException::getDescription() const throw()
    {
        return d_description;
    }
}


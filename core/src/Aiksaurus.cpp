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
 *
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
 * 02111-1307, USA.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "Aiksaurus.h"
#include "MeaningsFile.h"
#include "WordsFile.h"
#include "WordStream.h"

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

#if defined WIN32
	#include <windows.h>
	#define WIN32_LEAN_AND_MEAN
	// Default AIK_DATA_DIR is local directory
	std::string AIK_DATA_DIR(".\\");
	// Regestry Reading for AIK_DATA_DIR
	void ReadRegistry()
	{
		HKEY hKey;
		unsigned long lType;	
		DWORD dwSize;
		unsigned char* szValue = NULL;
		if( ::RegOpenKeyEx( HKEY_LOCAL_MACHINE, "Software\\Aiksaurus", 0, KEY_READ, &hKey) == ERROR_SUCCESS )
		{
			// Determine size of string
			if( ::RegQueryValueEx( hKey, "Data_Dir", NULL, &lType, NULL, &dwSize) == ERROR_SUCCESS )
			{
				szValue = new unsigned char[dwSize + 1];
				::RegQueryValueEx( hKey, "Data_Dir", NULL, &lType, szValue, &dwSize);
				AIK_DATA_DIR = (char*) szValue;
				delete[] szValue;
			}
		}
	}
	#if defined _DLL_BUILD
		//Add a DllMain Entry point
		BOOL APIENTRY DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved ) { return TRUE; }
	#endif
#endif

namespace AiksaurusImpl
{
    class ThesaurusImpl
    {
        private:      
            
        // Prevent copying and assignment.          
            ThesaurusImpl(const ThesaurusImpl& rhs);
            ThesaurusImpl& operator=(const ThesaurusImpl& rhs);
 
        // Data Members
            MeaningsFile d_meanings;        // the meanings file
            WordsFile d_words;              // the words file
            std::string d_word;             // current search term.
            int d_id;                       // id of d_word
            const int* d_links;             // ids of meaning sets for d_word 
            std::string d_currentSynonym;   // last synonym that was read
            std::string d_currentSimilar;   // last similar word that was read
            int d_similarID;                // current id of similar words
            int d_similarStop;              // id to stop similar words at
            
        // For each link, we will read a meaning set from the Meanings
        // file.  We'll receive a vector of words that are associated
        // with the meaning.  These will get put into meaning streams,
        // one for each meaning.  We also keep track of which meaning
        // we're currently on.
            vector<WordStream*> d_meaningStreams;
            vector<WordStream*>::size_type d_currentStream;
           
            
        public:

            ThesaurusImpl(const char* mfile, const char* wfile)
                throw(AiksaurusException);
            
            ~ThesaurusImpl() throw();

            const char* word() const throw();

            bool find(const char* word) throw(AiksaurusException);
            const char* next(int& id) throw(AiksaurusException);
            const char* similar() throw(AiksaurusException);
    };


    
ThesaurusImpl::ThesaurusImpl(const char* mfile, const char* wfile)
throw(AiksaurusException)
    : d_meanings(mfile), 
      d_words(wfile), 
      d_links(NULL), 
      d_similarID(0),
      d_similarStop(0),
      d_currentStream(0)
{
    try
    {
        const int size = WordsFile::maxWordLength() + 1;
        d_currentSimilar.reserve( size );
        d_currentSynonym.reserve( size );
    }
    
    catch(std::bad_alloc)
    {
        throw AiksaurusException(
                AiksaurusException::CANNOT_ALLOCATE_MEMORY
        );
    }
}


ThesaurusImpl::~ThesaurusImpl() throw()
{
    for(unsigned int i = 0;i < d_meaningStreams.size();++i)
        delete d_meaningStreams[i];
}


const char* 
ThesaurusImpl::word() const throw()
{
    return d_word.c_str();
}



bool 
ThesaurusImpl::find(const char* word) throw(AiksaurusException)
{
    try
    {
        d_word = word;  // might throw std::bad_alloc
    
        for(unsigned int i = 0;i < d_meaningStreams.size();++i)
            delete d_meaningStreams[i];
        d_meaningStreams.clear();
    
        d_currentStream = 0;
        d_links = 0;
 
        bool found = d_words.findWord(word, d_id);  // might throw AikException
       
        if (found) 
        {
            d_words.loadWord(d_id);         // might throw AiksaurusException
            d_links = d_words.getLinks();   
        
            for(int i = 0;d_links[i] != -1;++i)
            {
                // this might throw std::bad_alloc
                d_meaningStreams.push_back( 
                    new WordStream( d_meanings.getWords(d_links[i]) )
                );
            }
        }
        
        d_similarID = max(d_id - 10, 0);
        d_similarStop = min(d_similarID + 20, d_words.getSize());    
    
        return found; 
    }

    catch(std::bad_alloc)
    {
        throw AiksaurusException(
                AiksaurusException::CANNOT_ALLOCATE_MEMORY
        );
    }
}



const char* ThesaurusImpl::next(int& id) throw(AiksaurusException)
{
    if (d_currentStream >= d_meaningStreams.size())
        return "";
    
    int x = d_meaningStreams[d_currentStream]->next();    
    if (x < 0)
    {
        d_currentStream++;
        return next(id);
    }

    else
    {
        id = d_currentStream;
        d_words.loadWord(x); // might throw AiksaurusException
        d_currentSynonym = d_words.getWord();
    }    

    return d_currentSynonym.c_str();
}


const char* ThesaurusImpl::similar() throw(AiksaurusException)
{
    if (d_similarID < d_similarStop)
    {
        d_words.loadWord(d_similarID++); // might throw AiksaurusException
        d_currentSimilar = d_words.getWord();
    }

    else
    {
        d_currentSimilar = "";
    }

    return d_currentSimilar.c_str();
}

}


///////////////////////////////////////////////////////////////////////
//
//  AikSaurus Class -- Wraps around Implementation
//
///////////////////////////////////////////////////////////////////////

static const char* EMPTY_STRING = "";

Aiksaurus::Aiksaurus() throw()
: d_impl_ptr(0), d_error(EMPTY_STRING)
{
    try
    {
#if defined WIN32
		ReadRegistry();
#endif
	std::string base(AIK_DATA_DIR);
#ifdef HAVE_GETENV
	char * aikdatadir_envvar = getenv ("AIK_DATA_DIR");
	if (aikdatadir_envvar) base = std::string(aikdatadir_envvar);
#endif
	std::string mfile(base + "meanings.dat");
        std::string wfile(base + "words.dat");
        d_impl_ptr = new ThesaurusImpl(mfile.c_str(), wfile.c_str());
    }
    catch(std::bad_alloc)
    {
        d_error = AiksaurusException::MemoryError;
    }
    catch(AiksaurusException& e)
    {
        d_error = e.getDescription();
    }
}

Aiksaurus::Aiksaurus(const char * path_meanings, const char * path_words) throw()
: d_impl_ptr(0), d_error(EMPTY_STRING)
{
    try
    {
        d_impl_ptr = new ThesaurusImpl(path_meanings,path_words);
    }
    catch(std::bad_alloc)
    {
        d_error = AiksaurusException::MemoryError;
    }
    catch(AiksaurusException& e)
    {
        d_error = e.getDescription();
    }
}


Aiksaurus::~Aiksaurus() throw()
{
    delete d_impl_ptr;
}


const char* 
Aiksaurus::word() const throw()
{
    return (d_impl_ptr) 
        ? (d_impl_ptr->word())
        : (EMPTY_STRING);   
}


const char* 
Aiksaurus::error() const throw()
{
    return d_error;
}


bool 
Aiksaurus::find(const char* word) throw()
{
    try
    {
        return d_impl_ptr->find(word);
    }

    catch(AiksaurusException& e)
    {
        d_error = e.getDescription();
        return false;
    }
}

const char* 
Aiksaurus::next(int& meaning) throw()
{
    try
    {
        return d_impl_ptr->next(meaning);
    }

    catch(AiksaurusException& e)
    {
        d_error = e.getDescription();
        return EMPTY_STRING;
    }
}

const char* 
Aiksaurus::similar() throw()
{
    try
    {    
        return d_impl_ptr->similar();
    }

    catch(AiksaurusException& e)
    {
        d_error = e.getDescription();
        return EMPTY_STRING;
    }
}



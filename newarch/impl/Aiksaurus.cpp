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

#include "config.h"
#include "Aiksaurus.h"
#include "MeaningsFile.h"
#include "WordsFile.h"
#include "WordStream.h"
#include <string>
#include <iostream>

namespace AiksaurusImpl
{
    class ThesaurusImpl
    {
        private:      
                      
            ThesaurusImpl(const ThesaurusImpl& rhs);
            ThesaurusImpl& operator=(const ThesaurusImpl& rhs);
        
            MeaningsFile d_meanings;
            WordsFile d_words;
        
            std::string d_word;
            std::string d_currentSynonym;
            int d_id;
        
            const int* d_links;
                
            vector<WordStream*> d_meaningStreams;
            vector<WordStream*>::size_type d_currentStream;
            
            
            
        public:

            ThesaurusImpl(const char* mfile, const char* wfile);
            ~ThesaurusImpl();

            const char* word() const;

            const char* next(int& id);
            
            bool find(const char* word);

            const char* label(int meaning);

            const char* similar();

            const char* error();
    };
}


AiksaurusImpl::ThesaurusImpl::ThesaurusImpl(const char* mfile, const char* wfile)
: d_meanings(mfile), d_words(wfile), d_links(NULL)
{
    d_currentSynonym.reserve( WordsFile::maxWordLength() + 1 );
    d_currentStream = 0;
}


AiksaurusImpl::ThesaurusImpl::~ThesaurusImpl()
{

}


const char* 
AiksaurusImpl::ThesaurusImpl::word() const
{
    return d_word.c_str();
}


bool 
AiksaurusImpl::ThesaurusImpl::find(const char* word)
{
    d_word = word;
    
    for(unsigned int i = 0;i < d_meaningStreams.size();++i)
    {   
        delete d_meaningStreams[i];
    }   
    
    d_meaningStreams.clear();
    
    d_currentStream = 0;
    d_links = NULL;
    
    if ( (d_id = d_words.findWord(word)) == -1)
    {
        cout << "Word is not found." << endl;
        return false;
    }

    cout << "Word found: id is " << d_id << endl;
    
    d_words.loadWord(d_id);
    d_links = d_words.getLinks();

    for(int i = 0;d_links[i] != -1;++i)
    {
        d_meaningStreams.push_back( 
            new WordStream( d_meanings.getWords(d_links[i]) )
        );
    }
    
    cout << "Created " << d_meaningStreams.size() << " meaning streams." << endl;

    return true; 
}


const char* AiksaurusImpl::ThesaurusImpl::next(int& id)
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
        d_words.loadWord(x);
        d_currentSynonym = d_words.getWord();
    }    

    return d_currentSynonym.c_str();
}

const char* 
AiksaurusImpl::ThesaurusImpl::label(int meaning)
{
    assert(0);
    return "label() NOT YET IMPLEMENTED.";
}

const char* 
AiksaurusImpl::ThesaurusImpl::similar()
{
    assert(0);
    return "similar() NOT YET IMPLEMENTED.";
}

const char* 
AiksaurusImpl::ThesaurusImpl::error()
{
    assert(0);
    return "error() NOT YET IMPLEMENTED.";
}




///////////////////////////////////////////////////////////////////////
//
//  AikSaurus Class -- Wraps around Implementation
//
///////////////////////////////////////////////////////////////////////

AiksaurusImpl::Aiksaurus::Aiksaurus()
: d_impl_ptr(NULL)
{
    std::string base(AIK_DATA_DIR);
    std::string mfile(base + "meanings.dat");
    std::string wfile(base + "words.dat");
    d_impl_ptr = new ThesaurusImpl(mfile.c_str(), wfile.c_str());
}

AiksaurusImpl::Aiksaurus::~Aiksaurus()
{
    delete d_impl_ptr;
}

const char* 
AiksaurusImpl::Aiksaurus::word() const
{
    return d_impl_ptr->word();
}
		
bool 
AiksaurusImpl::Aiksaurus::find(const char* word)
{
    return d_impl_ptr->find(word);
}

const char* 
AiksaurusImpl::Aiksaurus::next(int& meaning)
{
    return d_impl_ptr->next(meaning);
}

const char* 
AiksaurusImpl::Aiksaurus::label(int meaning)
{
    return d_impl_ptr->label(meaning);
}

const char* 
AiksaurusImpl::Aiksaurus::similar()
{    
    return d_impl_ptr->similar();
}
const char* 
AiksaurusImpl::Aiksaurus::error()
{
    return d_impl_ptr->error();
}


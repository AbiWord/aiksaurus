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

#include "AiksaurusC.h"
#include "Aiksaurus.h"
#include <new>

static Aiksaurus *instance = 0;

int Aiksaurus_init()
{
    if (!instance)
        instance = new(std::nothrow) Aiksaurus;
    
    return (instance != 0); 
}

void Aiksaurus_destroy()
{
    delete instance;
    instance = 0;
}

const char* Aiksaurus_error()
{
    if (instance)
        return instance->error();
    else
        return "Error: Aiksaurus_error() called before Aiksaurus_init()";
}

const char* Aiksaurus_word()
{
    return((instance) ? (instance->word()) : (""));
}

int Aiksaurus_find(const char* word)
{
    return((instance) ? (instance->find(word)) : (0));
}

const char* Aiksaurus_next(int* meaning)
{
    return((instance) ? (instance->next(*meaning)) : (""));
}

const char* Aiksaurus_similar()
{
    return((instance) ? (instance->similar()) : (""));
}


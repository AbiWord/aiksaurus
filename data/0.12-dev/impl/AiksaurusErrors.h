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

#ifndef INCLUDED_AIKSAURUS_ERRORS_H
#define INCLUDED_AIKSAURUS_ERRORS_H

namespace AiksaurusImpl
{
    class AiksaurusError
    {
        private:

            const char* d_description;
            
        public:

            static const char* SUCCESS;

            static const char* CANNOT_OPEN_MEANINGS_FILE;
            static const char* CORRUPT_MEANINGS_FILE;

            static const char* CANNOT_OPEN_WORDS_FILE;
            static const char* CORRUPT_WORDS_FILE;
            
            static const char* CANNOT_ALLOCATE_MEMORY;

            AiksaurusError();
            ~AiksaurusError();

            void setDescription(const char* str);
            const char* getDescription() const;

            bool isError() const;
    };
}

#endif // INCLUDED_AIKSAURUS_ERRORS_H

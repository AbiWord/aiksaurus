/*
 * AiksaurusGTK - A GTK interface to the AikSaurus library
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
 */

#ifndef INCLUDED_JARED_GPL_AIKSAURUSGTK_H
#define INCLUDED_JARED_GPL_AIKSAURUSGTK_H

#include <new>

namespace AiksaurusGTK_impl
{
    class DialogImpl;
    class AiksaurusGTK
    {
        private:
            AiksaurusGTK(const AiksaurusGTK& rhs);
            AiksaurusGTK& operator=(const AiksaurusGTK& rhs);
            
            DialogImpl* d_impl_ptr;
            
        public:
            AiksaurusGTK() throw(std::bad_alloc);
            ~AiksaurusGTK() throw();
            
            void setTitle(const char* title) throw();
           
            void setInitialMessage(const char* message) throw(std::bad_alloc); 
            void showReplacebar() throw();
            void hideReplacebar() throw();
            
            const char* runThesaurus(const char* word) throw();
    };
}

typedef AiksaurusGTK_impl::AiksaurusGTK AiksaurusGTK;

#endif // INCLUDED_JARED_GPL_AIKSAURUSGTK_H

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

#include "AiksaurusGTK_strlist.h"
#include "AiksaurusGTK_utils.h"
#include <cstring>


//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Creation and Destruction                                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

AiksaurusGTK_strlist::AiksaurusGTK_strlist()
{
	d_size = 0;
	d_list_ptr = NULL;
}


static void destroyString(void* str, gpointer data)
{
	char* x = static_cast<char*>(str);
	delete[] x;
}

AiksaurusGTK_strlist::~AiksaurusGTK_strlist()
{
	g_list_foreach(d_list_ptr, destroyString, NULL);
	g_list_free(d_list_ptr);
}



//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Insertion Routines                                                 //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

void AiksaurusGTK_strlist::push_back(const char* str)
{
	char* x = AiksaurusGTK_strCopy(str);
	d_list_ptr = g_list_append(d_list_ptr, x);
	d_size++;
}

void AiksaurusGTK_strlist::push_front(const char* str)
{
	char* x = AiksaurusGTK_strCopy(str);
	d_list_ptr = g_list_prepend(d_list_ptr, x);
	d_size++;
}




//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Deletion Routines                                                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

GList* AiksaurusGTK_strlist::find_first(const char* str)
{
	for(GList* iterator = g_list_first(d_list_ptr);
	    iterator != NULL;iterator = g_list_next(iterator))
	{
		const char* x = static_cast<const char*>(iterator->data);

		if (AiksaurusGTK_strEquals(x, str))
		{
			return iterator;
		}
	}

	return NULL;
}

void AiksaurusGTK_strlist::remove_first(const char* str)
{
	GList* iterator = find_first(str);
	
	if (iterator == NULL)
		return;
	
	g_list_remove_link(d_list_ptr, iterator);
	delete[] static_cast<char*>(iterator->data);
	g_list_free(iterator);

	d_size--;
}

void AiksaurusGTK_strlist::remove_last_element()
{
	GList* iterator = g_list_last(d_list_ptr);
	
	if (iterator == NULL)
		return;

	g_list_remove_link(d_list_ptr, iterator);
	delete[] static_cast<char*>(iterator->data);
	g_list_free(iterator);

	d_size--;
}



//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Inspection Routines                                                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

const GList* AiksaurusGTK_strlist::list() const
{
	return d_list_ptr;
}

unsigned int AiksaurusGTK_strlist::size() const
{
	return d_size;
}





//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Debugging Routines                                                 //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
#ifndef NDEBUG

#include <iostream>
using namespace std;

static 
void debugHelper(void* str, void* data)
{
	char* x = static_cast<char*>(str);
	cout << "   " << x << endl;
}

void AiksaurusGTK_strlist::debug()
{
	cout << "AiksaurusGTK_strlist::debug() { " << endl;
	cout << " Size of d_list_ptr is: " << size() << endl;
	cout << " Address of d_list_ptr is: " << d_list_ptr << endl;
	cout << " Contents of d_list_ptr are: " << endl;
	g_list_foreach(d_list_ptr, debugHelper, NULL);
	cout << "}" << endl;
}

#endif // NDEBUG

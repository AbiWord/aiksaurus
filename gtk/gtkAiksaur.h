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

#ifndef INCLUDED_JARED_GPL_GTKAIKSAUR_H
#define INCLUDED_JARED_GPL_GTKAIKSAUR_H

//
// ActivateThesaurus
// -----------------
//   
//   Arguments:
//
//     Takes a character pointer to a string that the user wants to search 
//     for.  Usually this is whatever word their cursor is over, or whatever 
//     word is selected when the user activates the thesaurus dialog.
//
//     If there is no word, you can safely pass either a blank string ("") 
//     or you can pass NULL and it will be interpreted as a blank string.
//  
//  
//   Return Value:
//   
//     A character pointer to a (possibly) new word that the user wants to 
//     replace the word they searched for with.
//     
//     Note: you should not attempt to delete/free the returned string 
//     yourself.
//   
const char* ActivateThesaurus(const char* search);

#endif // INCLUDED_JARED_GPL_GTKAIKSAUR_H

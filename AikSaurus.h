/*
 * AikSaurus - An open source thesaurus library
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

#ifndef INCLUDED_GPL_JARED_AIKSAURUS_H
#define INCLUDED_GPL_JARED_AIKSAURUS_H

class AikSaurusImpl;
class AikSaurus
{
	private:

		AikSaurusImpl *d_impl_ptr;
		
		// prevent copying or assignment, since this is 
		// a large object to create and destroy.
		AikSaurus(const AikSaurus& rhs);
		const AikSaurus& operator=(const AikSaurus& rhs);
		
	public:

		// bit masks for part-of-speech identification.
		// These can be used in a mask fashion to determine if a word
		// might be a noun, verb, adjective, etc.  Since some words can
		// be many of these, (for instance, the word "bully" can be a 
		// noun, "the bully went home", a verb: "don't bully me, mister!",
		// etc.) you just mask with what you want.
		// see the 'next' function for more information.
		enum POS {
			Noun = 0x01, 
			Verb = 0x02,
			Adjective = 0x04,
			Adverb = 0x08,
			Other = 0x10,
			Unknown = 0x20
		}; 
		
		// constructor takes an optional argument for
		// the data directory
		AikSaurus(const char* data_dir = 0);
		~AikSaurus();

		
		// call 'word' to figure out what word is current.
		const char* word() const;
		
		
		// call 'find' to set up which word you want 
		// the results from. Returns true if the word is
		// found, false otherwise.
		bool find(const char* word);

		
		// call 'next' repeatedly to return one synonym
		// at a time, until it returns empty string.
		// you do not have to delete this string, but
		// the next call to 'next' will overwrite it.
		// pos is set to a part-of-speech mask. you can 
		// test it using: (pos & AikSaurus::Noun), etc.
		const char* next(char& pos);

		
		// call 'similar' repeatdly to return one 
		// "nearby word" at a time.  these are not 
		// synonyms: they are known words that are 
		// alphabetically near the searched-for word.
		const char* similar();
		
		
		// call 'error' to find out if something went 
		// wrong.  will be empty if no problems.  you
		// do not have to delete this string, it is 
		// managed automatically.
		const char* error() const;

		
		// call 'count' to find out how many synonyms
		// there are before extracting them.  it will
		// return 0 if the word is not found.
		unsigned int count() const;
};

#endif // INCLUDED_GPL_JARED_AIKSAURUS_H

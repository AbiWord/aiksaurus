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

#include "config.h"
 
#include "AikSaurus.h"		// main header for the library
#include "StringLoopQueue.h"	// used to create 'alphabetically similar' entries.
#include "bzreader.h"		// lets us easily read bz2 compressed files
#include <string>		// we use std::string for just about everything.
#include <vector>		// we store index words in a vector.
#include <fstream>		// used so we can read the index file.
#include <strstream>		// used to convert from integer to string.
using namespace std;


//
// Number of Similar Words
// -----------------------
//   The value of this constant controls how many "similar words"
//   to attempt to return.  
//
static const int NUM_SIMILAR_WORDS = 20;



//
// AikSaurusSynStream Class
// ------------------------
//   Reads in a string of synonyms, and outputs them one at a time.
//
class AikSaurusSynStream
{
	private:

		const std::string& d_results_ref;
		unsigned int d_position;

	public:

		AikSaurusSynStream(const std::string& str)
		: d_results_ref(str), d_position(0) 
		{}

		bool operator>>(std::string& str)
		{
			str = "";
			for(;d_position < d_results_ref.size();++d_position)
			{
				if (d_results_ref[d_position] == ' ')
				{
					d_position++;
					return true;
				}

				str += d_results_ref[d_position];
			}

			return (str != "");
		}
};














class AikSaurusImpl
{
	private:

	//
	// Globalish sort of stuff
	//
	
		// 
		// location of data directory.
		//
		AikString d_dataDirectory;


		// 
		// static error strings.
		//
		static const char* s_noError;
		static const char* s_errorReadingIndex;
		static const char* s_errorReadingDatafile;


		//
		// pointer to the current error status.
		//
		const char *d_error;

		
		//
		// topwords is a list of the top word in each 
		// of our datafiles, which we use to figure 
		// out where our other words should be.
		//
		vector<AikString> d_topwords;


	//
	// Current Search sort of stuff
	//


		//
		// similar words queue
		// this is a special kind of circular queue that 
		// automatically overwrites its oldest entries.
		// this way, we just keep adding to the queue as 
		// we search for the word, and the most recent 
		// words end up in the queue.
		// 
		StringLoopQueue d_similarWords;

		
		// 
		// d_currentSimilar is a buffer to use hold the 
		// current 'similar word' that has been returned,
		// so that we can just return a const char* from 
		// the similar() function.
		// 
		string d_currentSimilar;

		//
		// synonym stream
		// the synonyms themselves are kept in the string 
		// d_currentSynonyms.  the synstream pointer lets
		// us very easily read the next synonym from this
		// list.
		//
		AikString d_currentSynonyms;
		AikSaurusSynStream *d_synstream_ptr;


		//
		// currentResult keeps a string of our
		// current result that we're returning.
		// 
		string d_currentResult;

		

	//
	// Private member functions 
	//
	
		// 
		// prevent copying and assignment.
		// these are declared private but never defined.
		//
		AikSaurusImpl(const AikSaurusImpl& rhs);
		const AikSaurusImpl& operator=(const AikSaurusImpl& rhs);


		//
		// basic helper functions.  
		//   replace characters in strings, and convert
		//   integers to strings.
		//
		
		inline 
		void intToString(int i, string& str) const;


		inline
		bool readEntry(BZReader& bzin, AikString& key, AikString& synonyms);

		bool cleanupSimilar(BZReader& bzin);


		//
		// lookupFile lets us figure out what file a word
		// should be in.
		//
		inline 
		int lookupFile(const AikString& word);


		#ifndef NDEBUG
		void debug();
		#endif

	public:

		// 
		// creation and destruction
		//
		AikSaurusImpl(const char* data_dir);
		~AikSaurusImpl();


		// 
		// simple function to figure out what our current 
		// error status is.
		//
		inline
		const char* error() const;


		// 
		// find actually sets us up to return synonyms
		// for the word 'word'.
		//
		inline
		bool find(const char* findme);


		//
		// next returns a string for the next synonym.
		//
		inline
		const char* next(char& pos);


		// 
		// similar returns "known words" that are 
		// alphabetically nearby the requested word.
		// 
		inline
		const char* similar();
};


// 
// AikSaurusImpl Error Strings
// ---------------------------
//   These are kept statically within the AikSaurusImpl class,
//   and the d_error pointer is set to whichever one is relevant.
//
	const char* AikSaurusImpl::s_noError = 
		"";

	const char* AikSaurusImpl::s_errorReadingIndex =
		"Error reading thesaurus index.txt datafile.";

	const char* AikSaurusImpl::s_errorReadingDatafile = 
		"Error reading a thesaurus datafile.";



#ifndef NDEBUG
//
// AikSaurusImpl::debug()
// ----------------------
//   debug method which isn't normally available.  useful for 
//   developers.
//
void AikSaurusImpl::debug()
{
	cout << "AikSaurusImpl::debug() information: " << endl;
	cout << "Reading data from: " << d_dataDirectory.c_str() << endl;
	cout << "Number of words in d_topwords: " << d_topwords.size() << endl;
	cout << "Current value of d_currentResult: " << d_currentResult << endl;
	cout << "Current error status: " << d_error << endl;
	cout << "d_synstream_ptr value: " << d_synstream_ptr << endl;
	cout << endl;
}


#endif


//
// AikSaurusImpl::AikSaurusImpl(const char* data_dir)
// --------------------------------------------------
//   Loads the index words list into the d_topwords vector
//   and returns.  Should be fairly fast since the index 
//   list is typically very small.
//   
AikSaurusImpl::AikSaurusImpl(const char* data_dir)
: d_error(s_noError), 
  d_similarWords(NUM_SIMILAR_WORDS),
  d_synstream_ptr(NULL)
{ 
	if (data_dir != 0) 
		d_dataDirectory = data_dir;
	else
		d_dataDirectory = AIK_DATA_DIR;

	// Open the index.txt file from the data directory.
	AikString indexfile(d_dataDirectory);
	indexfile += "index.txt";
	
	ifstream index(indexfile.c_str());

	string x;
	while(index >> x)
	{
		AikString xstr(x.c_str());
		xstr.replaceAll(':', ' ');
		d_topwords.push_back(xstr);
	}

	if (!d_topwords.size())
	{
		d_error = s_errorReadingIndex;
	}
}



//
// AikSaurusImpl::~AikSaurusImpl()
// -------------------------------
//   Destructor: destroy the results strstream if it is allocated.
//
AikSaurusImpl::~AikSaurusImpl()
{
	if (d_synstream_ptr)
	{
		delete d_synstream_ptr;
	}
}



//
// AikSaurusImpl::error()
// ----------------------
//   Returns the d_error pointer to indicate if there is an error
//   with the thesaurus or not.
//
inline
const char* AikSaurusImpl::error() const
{
	return d_error;
}



// 
// AikSaurusImpl::intToString(int i, string& str)
// ----------------------------------------------
//   Converts an integer to a string using the strstream 
//   class.  This is used to convert the datafile number
//   into it's name.
//
inline
void AikSaurusImpl::intToString(int i, string& str) const
{
	strstream ss;
	ss << i;
	ss >> str;
}



//
// AikSaurusImpl::lookupFile()
// ----------------------------
//   This function takes a word and compares it against the 
//   index list.  It performs a binary search on the index
//   list, attempting to find the word or find out which file
//   the word should be in.  Returns the number of the file
//   the word should be in, if it's in the thesaurus.
//   
inline
int AikSaurusImpl::lookupFile(const AikString& word)
{
	int low = 0, high = d_topwords.size() - 1;

	while(low <= high)
	{
		unsigned int mid = (high + low) / 2;
		
		if (word < d_topwords[mid])
		{
			high = mid - 1;
		}
		
		else if (word > d_topwords[mid])
		{
			low = mid + 1;
		}

		else
		{
			// happens to be the top word in the file.
			// this is ok, just return the file number
			return mid;
		}
	}

	// if we get to here, then low has surpassed high.
	// most binary searches return a failure at this point,
	// but this is actually normal for us.  it means that 
	// if the word exists, it will be in the same file as
	// 'high'.
	
	return high;
}



//
// AikSaurusImpl::readEntry
// ------------------------
//   Reads a line from the thesaurus file, putting the keyword
//   into 'key' and the synonyms into 'synonyms' as a comma-
//   delimited string.
//   
inline
bool AikSaurusImpl::readEntry(BZReader& bzin, AikString& key, AikString& synonyms)
{
	if (!(bzin >> key))
	{
		d_error = bzin.error();
		return false;
	}
	
	if (!(bzin >> synonyms))
	{
		d_error = bzin.error();
		return false;
	}	

	return true;
}



//
// AikSaurusImpl::cleanupSimilar()
// -------------------------------
//   Called when the word has either been found or we have 
//   concluded that the word does not exist.  Continues to 
//   read from the stream enough to get the "similar" list
//   to be balanced.  In other words, we want to have half
//   of the entries in the similar list be alphabetically
//   greater than the actual word, and the other half 
//   alphabetically less.  This ensures that this is the 
//   case.
//   
bool AikSaurusImpl::cleanupSimilar(BZReader& bzin)
{
	int stop = d_similarWords.size() / 2;

	AikString key, syns;
	for(int i = 0;i < stop;++i)
	{
		if (!readEntry(bzin, key, syns))
			return false;

		d_similarWords.push(key);
	}

	return true;
}



//
// AikSaurusImpl::find(const char* findme)
// ---------------------------------------
//   Load the results buffer with synonyms of the word
//   that they want to find.
//
inline
bool AikSaurusImpl::find(const char* findme)
{
	//
	// Create a lower-case version of the word we're searching
	// for.
	// 
	AikString word(findme);
	word.strLower();        
	
	
	// 
	// delete the results pointer from the previous 
	// search if it exists.
	//
	if (d_synstream_ptr)
	{
		delete d_synstream_ptr;
		d_synstream_ptr = NULL;
	}


	// 
	// now, figure out what datafile the word should 
	// be in.  we have a list of the top words from 
	// all the files, in our index.txt file.  So, we 
	// figure out what file it's supposed to be in
	// with a binary search against these.
	//
	int file = lookupFile(word);
	
	if (file == -1)
	{
		return false;
	}
	

	// 
	// now, we need to open this file.  to do that, we 
	// first must convert from number to string.
	//

	string datafile;
	intToString(file, datafile);
	datafile = string(d_dataDirectory.c_str()) + datafile + ".bz2";

	//
	// now we can open the file with our bz2 reader 
	// class.  we will do a simple sequential search 
	// on the file until we find the word we're after.
	// this is fast enough if our datafiles are small.
	//
	
	BZReader bzin(datafile.c_str());

	d_error = bzin.error();
	if (d_error[0] != '\0')
	{
		return false;
	}

	AikString key;

	while(readEntry(bzin, key, d_currentSynonyms))
	{
		// build our similar words list as we go.
		d_similarWords.push(key);
		
		if (key == word) // found the right word.
		{
			d_currentSynonyms.replaceAll(',', ' ');
		
			string Hack(d_currentSynonyms.c_str());
			d_synstream_ptr = new AikSaurusSynStream(Hack);
			cleanupSimilar(bzin);
			return true;
		}
		
		else if (key < word)
		{
			// skip this word.

			// read was successful.  we don't want these
			// results though, so just do nothing.
		}

		else  
		{
			// key > word means not in file.  stop searching now.
			cleanupSimilar(bzin);
			return false;
		}
	}

	// Either:
	//   (1) the bzreader had an error, or
	//   (2) the user entered a word that would fall 'between files',
	//       and we don't have it.  
	//       
	//   In either case, we will return false, so we'll just set our 
	//   error to match bzin's error before returning and we should be 
	//   ok.
	d_error = bzin.error();
	return false;
}


//
// AikSaurusImpl::next()
// ---------------------
//   Returns the next synonym for the current word.
//   Returns an empty string if no more synonyms exist.
//
inline 
const char* AikSaurusImpl::next(char& pos)
{
	d_currentResult = "";
	
	if (d_synstream_ptr)
	{
		(*d_synstream_ptr) >> d_currentResult;
	}

	if (d_currentResult.size())
	{
		// first, extract part-of-speech information.
		int x = d_currentResult[d_currentResult.size() - 1] & 0x7F;
		pos = x;
		
		d_currentResult = d_currentResult.substr(0, d_currentResult.size() - 1);
	}

	return d_currentResult.c_str();
}


inline
const char* AikSaurusImpl::similar()
{
	d_currentSimilar = d_similarWords.pop().c_str();

	return d_currentSimilar.c_str();
}


//
// AikSaurus Class Implementation -----------------------------------
//

AikSaurus::AikSaurus(const char* data_dir)
: d_impl_ptr(new AikSaurusImpl(data_dir))
{

}

AikSaurus::~AikSaurus()
{
	delete d_impl_ptr;
}

bool AikSaurus::find(const char* word)
{
	return d_impl_ptr->find(word);
}

const char* AikSaurus::similar()
{
	return d_impl_ptr->similar();
}

const char* AikSaurus::next(char& pos)
{
	return d_impl_ptr->next(pos);
}

const char* AikSaurus::error() const
{
	return d_impl_ptr->error();
}

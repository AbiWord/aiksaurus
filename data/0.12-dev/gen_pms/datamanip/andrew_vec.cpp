#include "AikSaurus.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void checkError(const AikSaurus& T)
{
	const char* err = T.error();
	
	if (err[0] != '\0')
	{
		cout << "Error: " << err << endl;
		exit(1);
	}
}

//
// fillSet
// -------
// 'word' is looked up in AikSaurus, and the vector v is filled with it's synonyms 
//
void fillSet( const char *word, vector<string> &v )
{
    AikSaurus T;
    char code;

    v.clear();

    if ( T.find( word ) )
    {
        for(const char* result = T.next(code); result[0] != '\0'; result = T.next(code))
        {
            v.push_back( result );
        }
    }

//    sort( v.begin(), v.end() );
}

//
// setInt
// ------
// This function makes 'a' the set intersection of vectors 'a' and 'b'
// It is the mathematical equivalent of a = a^b
//
void setInt( vector<string> &a, vector<string> &b )
{
    vector< string > result;

    set_intersection( a.begin(), a.end(), b.begin(), b.end(), 
        inserter( result, result.end() ) );

    a.swap( result );
}

//
// equivClass
// ----------
// This function takes two words and propogates their appropriate class into rval
//
void equivClass( const char *first, const char *second, vector<string> &rval )
{
    rval.clear();

    vector< string > candidates;
    vector< string > tmp;
	
    fillSet( first, candidates );
    rval.push_back( first );

    fillSet( second, tmp );
    rval.push_back( second );

    sort( rval.begin(), rval.end() );

    setInt( candidates, tmp );

    while ( ! candidates.empty() )
    {
        fillSet( candidates.back().c_str(), tmp );
        if ( includes( tmp.begin(), tmp.end(), rval.begin(), rval.end() ) )
        {
            rval.push_back( candidates.back() );
            sort( rval.begin(), rval.end() );
            setInt( candidates, tmp );
        }
        else
        {
            candidates.pop_back();
        }
    }
}



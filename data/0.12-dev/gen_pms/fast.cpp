#include "fast.h"
#include <fstream>
#include <strstream>
using namespace std;

AikSaurusFAST::AikSaurusFAST()
{
    ifstream fin("thesaurus.in");
    string index, words;

    while(fin >> index >> words)
    {
        vector<string> foo;
        for(unsigned int i = 0;i < words.size();++i)
        {
            if (words[i] == ',') words[i] = ' ';
        }
        
        istrstream ss(words.c_str());
        string str;
        
        while(ss >> str)
        foo.push_back(str);

        d_data.insert(make_pair(index, foo));
    }
}

const vector<string>& AikSaurusFAST::getSynonyms(const string& word)
{
    map<string, vector<string> >::iterator thing = d_data.find(word);

    if (thing == d_data.end())
    {
        return d_null;
    }

    else
    {
        return thing->second;
    }
}


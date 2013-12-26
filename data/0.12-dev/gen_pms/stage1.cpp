//
// stage1
// input: single word
// output: preliminary meaning classes on lines separated by spaces.
//

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include "fast.h"

static AikSaurusFAST Thesaurus;   


void maximizeClass(vector<string>& meaning, int place)
{
    const vector<string>& synonyms = Thesaurus.getSynonyms(
            meaning[place]
    );
    
    for(int i = 0;i < synonyms.size();++i)
    {
        const vector<string>& subsyns = Thesaurus.getSynonyms(
                synonyms[i]
        );

        sort( meaning.begin(), meaning.end() );

        if (includes(subsyns.begin(), subsyns.end(),
                    meaning.begin(), meaning.end()))
        {
            meaning.push_back(synonyms[i]);
        }
    }
}


bool wordAlreadyInClass(
    const vector<vector<string> >& classes, 
    const string& word)
{
    for(int i = 0;i < classes.size();++i)
    {
        for(vector<string>::const_iterator x = classes[i].begin(); x != classes[i].end(); ++x)
        {
            if ((*x) == word) 
                return true;
        }
    }
    
    return false;
}


int main(int argc, const char** argv)
{
    string word;
    if (argc < 2)
    {
        cout << "Enter word to build meanings for: " << flush;
        cin >> word;
    }
    else
    {
        word = argv[1];
    }

    const vector<string>& topsyns = Thesaurus.getSynonyms(word);

    vector< vector<string> > classes;
   
    for(int i = 0;i < topsyns.size();++i)
    {
        if (!wordAlreadyInClass(classes, topsyns[i]))
        {
            classes.push_back(vector<string>());
            int index = classes.size() - 1;
            classes[index].reserve(10);
            classes[index].push_back(word);
            classes[index].push_back(topsyns[i]);
            maximizeClass(classes[index], 1);

            sort(classes[index].begin(), classes[index].end());

            copy(classes[index].begin(), classes[index].end(),
                    ostream_iterator<string>(cout, " "));

            cout << endl;
        }
    }
    
    return 0;
}





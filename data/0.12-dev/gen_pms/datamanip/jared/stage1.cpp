//
// stage1
// input: single word
// output: preliminary meaning classes on lines separated by spaces.
//

#include <iostream>
#include <AikSaurus.h>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

AikSaurus Thesaurus;   


void getSynonyms(const std::string& str, vector<string>& syns)
{
    if (Thesaurus.find(str.c_str()))
    {
        syns.reserve(Thesaurus.count() + syns.size());
        char p;
    
        for(const char* r = Thesaurus.next(p);r[0] != 0;r = Thesaurus.next(p))
        {
            syns.push_back(r);
        }
    }
}


void getSynonyms(const std::string& str, set<string>& syns)
{
    if (Thesaurus.find(str.c_str()))
    {
        char p;
        for(const char* r = Thesaurus.next(p);r[0] != 0;r = Thesaurus.next(p))
        {
            syns.insert(r);
        }
    }
}


void maximizeClass(vector<string>& meaning, int place)
{
    vector<string> synonyms;
    getSynonyms(meaning[place].c_str(), synonyms);

    for(int i = 0;i < synonyms.size();++i)
    {
        vector<string> subsyns;
        getSynonyms(synonyms[i], subsyns);

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

    vector<string> topsyns;
    getSynonyms(word, topsyns);

    vector< vector<string> > classes;
    classes.reserve(Thesaurus.count());
   
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





#include "Words.h"
#include <strstream>
using namespace std;

Word::Word(const char* line)
{
    istrstream ss(line);
    ss >> d_name;

    int x;
    while(ss >> x)
    {
        d_meanings.push_back(x);
    }
}

void extractWords(istream& file, vector<Word>& words)
{
    char buf[64000];

    while(file.getline(buf, 64000))
    {
        words.push_back(Word(buf));    
    }
}   


#ifndef INCLUDED_WORDS_H
#define INCLUDED_WORDS_H

#include <vector>
#include <string>

class Word
{
    private:
        std::string d_name;
        std::vector<int> d_meanings;
        
    public:   
        Word(const char* line);
        
        std::string& getWord()
        {
            return d_name;
        }
        
        std::vector<int>& getMeanings()
        {
            return d_meanings;
        }
};

void extractWords(istream& file, vector<Word>& words);

#endif // INCLUDED_WORDS_H

#ifndef INCLUDED_FASTSAUR_H
#define INCLUDED_FASTSAUR_H

#include <vector>
#include <string>
#include <map>

class AikSaurusFAST
{
    private:

        std::vector<std::string> d_null;
        std::map<std::string, std::vector<std::string> > d_data;

    public:

        AikSaurusFAST();
        
        const std::vector<std::string>& getSynonyms(const string& word);
};

extern AikSaurusFAST Thesaurus;

#endif 

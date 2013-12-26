#include "FastSaurus.h"
#include "Ratios.h"
    
double 
returnLinkRatio(const std::string& word, const MeaningSet& meanings)
{
    double ratio = 0;
    for(MeaningSet::const_iterator i = meanings.begin();i != meanings.end();++i)
    {
        if (*i == word)
            continue;
        
        const vector<string>& synonyms = Thesaurus.getSynonyms(*i);

        for(vector<string>::const_iterator j = synonyms.begin(); j != synonyms.end();++j)
        {
            if (*j == word)
            {
                ratio += double(1) / double(meanings.size() - 1);
                break;
            }
        }
    }

    return ratio;
}



double
directLinkRatio(const std::string& word, const MeaningSet& meanings)
{
    double ratio = 0;

    const vector<string>& wordmean = Thesaurus.getSynonyms(word);
    
    for(MeaningSet::const_iterator i = meanings.begin(); i != meanings.end(); ++i)
    {
        if (*i == word)
            continue;

        for(vector<string>::const_iterator j = wordmean.begin(); j != wordmean.end(); ++j)
        {
            if (*i == *j)
            {
                ratio += double(1) / double(meanings.size() - 1);
                break;
            }
        }
    }

    return ratio;
}



double
meanReturnLinkRatio(const MeaningSet& meanings)
{
    double ratio = 0;
    
    for(MeaningSet::const_iterator i = meanings.begin();i != meanings.end();++i)
    {
        ratio += returnLinkRatio(*i, meanings);
    }

    ratio /= meanings.size();
    
    return ratio;
}



double
meanDirectLinkRatio(const MeaningSet& meanings)
{
    double ratio = 0;

    for(MeaningSet::const_iterator i = meanings.begin(); i != meanings.end(); ++i)
    {
        ratio += directLinkRatio(*i, meanings);
    }

    ratio /= meanings.size();

    return ratio;
}


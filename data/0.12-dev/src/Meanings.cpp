#include "Meanings.h"
#include <strstream>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

static const int MAX_LINE_SIZE = 64000;


void printMeaningSet(std::ostream& out, const MeaningSet& set)
{
    out << "{ ";
    copy(set.begin(), set.end(), ostream_iterator<string>(cout, ", "));
    out << " }";
}


bool inMeaningSet(const string& str, const MeaningSet& set)
{
    return find(set.begin(), set.end(), str) != set.end();
}


// extractMeaningSet: 
//   generate a meaning set from a line of input.
//   words assumed to be separated by spaces.
void extractMeaningSet(const char* line, MeaningSet& set)
{
    istrstream ss(line);
    string str;

    while(ss >> str)
    {
        set.push_back(str);
    }
}


void extractMeaningSet(
        const char* line, 
        MeaningSet& set, 
        double& dlr, 
        double& rlr
)
{
    istrstream ss(line);
    ss >> dlr;
    ss >> rlr;

    string str;
    while(ss >> str)
    {
        set.push_back(str);
    }
}

    
// extractMeaningFamily
//   generate a family of meaning sets from an
//   input file.  file format: one meaning set
//   per line, words separated by spaces.
void extractMeaningFamily(std::istream& in, MeaningFamily& family)
{
    char buf[MAX_LINE_SIZE];

    while(in.getline(buf, MAX_LINE_SIZE))
    {
        family.push_back(MeaningSet());
        extractMeaningSet(buf, family.back()); 
    }
}

void extractMeaningFamily(
        std::istream& in, 
        MeaningFamily& family,
        vector<double>& dlr,
        vector<double>& rlr
)
{
    char buf[MAX_LINE_SIZE];
    double dlr_temp, rlr_temp;
    
    while(in.getline(buf, MAX_LINE_SIZE))
    {
        family.push_back(MeaningSet());
        extractMeaningSet(buf, family.back(), dlr_temp, rlr_temp);
        dlr.push_back(dlr_temp);
        rlr.push_back(rlr_temp);
    }
}

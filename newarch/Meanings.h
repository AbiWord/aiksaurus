#ifndef INCLUDED_MEANINGS_H
#define INCLUDED_MEANINGS_H

#include <iostream>
#include <vector>
#include <string>


    // MeaningSet 
    //   a single meaning set.  A vector of strings that
    //   are somehow related.
    typedef std::vector<std::string> MeaningSet;


    // MeaningFamily
    //   a family of meaning sets.  This represents a 
    //   collection of meaning sets.
    typedef std::vector<MeaningSet> MeaningFamily;


    // extractMeaningSet: 
    //   generate a meaning set from a line of input.
    //   words assumed to be separated by spaces.
    void extractMeaningSet(
            const char* line, 
            MeaningSet& set
    );
    
    // extractMeaningSet:
    //   rlr+dlr version of same function.
    void extractMeaningSet(
            const char* line, 
            MeaningSet& set, 
            double& dlr, double& rlr
    );

    
    // extractMeaningFamily
    //   generate a family of meaning sets from an
    //   input file.  file format: one meaning set
    //   per line, words separated by spaces.
    void extractMeaningFamily(
            std::istream& lines, 
            MeaningFamily& family
    );

    // extractMeaningFamily: rlr/dlr version
    void extractMeaningFamily(
            std::istream& lines, 
            MeaningFamily& family,
            vector<double>& dlrs, 
            vector<double>& rlrs
    );

    bool inMeaningSet(const string& str, const MeaningSet& ms);

    class ostream;
    void printMeaningSet(ostream& out, const MeaningSet& ms);
    
#endif // INCLUDED_MEANINGS_H

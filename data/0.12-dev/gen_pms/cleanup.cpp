#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <strstream>
#include <algorithm>
using namespace std;

#include "setutils.h"

#define DEBUG_SUBSETS 0
#define DEBUG_SMALLMERGE 0


// SMALLMERGE_RATIO: the golden ratio used for smallmerge algorithm.
const double SMALLMERGE_RATIO = .5;

// PITHY_FILTER: remove all meanings with less than this many synonyms listed.
const unsigned int PITHY_FILTER = 10;


template<class T>
void printvec(const vector<T>& v, const char* label)
{
    cout << label << " = { ";
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, ", "));
    cout << "}\n";
}   
    

void cleanup(vector< vector<string> >& classes, vector< vector<string> >& output)
{
    output.reserve(50);

    // First, destroy any classes that only have two words.  There
    // tend to be extremely obscure.
    for(int i = 0;i < classes.size();++i)
    {
        if (classes[i].size() == 2)
            classes[i].clear();
    
        sort(classes[i].begin(), classes[i].end());
    }

    for(int i = 0;i < classes.size();++i)
    {
        if (classes[i].empty())
            continue;
        
        for(int j = i+1;j < classes.size();++j)
        {
            if (classes[j].empty())
                continue;
            
            vector<string> left, right, common;
            set_comparison(left, right, common, classes[i], classes[j]);

            
            // Now we will delete proper subsets. There shouldn't
            // be many of these.
            if (left.empty())
            {
                #if DEBUG_SUBSETS
                cout << i << " is a subset of " << j << endl;
                printvec(classes[i], "  lhs");
                printvec(classes[j], "  rhs");
                #endif // DEBUG_SUBSETS             
                classes[i].clear();
                break;
            }
            else if (right.empty())
            {
                #if DEBUG_SUBSETS
                cout << j << " is a subset of " << i << endl;
                printvec(classes[i], "  lhs");
                printvec(classes[j], "  rhs");
                #endif
                classes[j].clear();
            }

            
            // Now we will attempt to merge small sets into large sets.
            // There should (hopefully) be many of these merges.
            //
            // We will make the convention that merges will be placed
            // into classes[i].  In other words, we want classes[i] to 
            // become our large set, and clear out classes[j].
            double lratio = double(common.size()) / double(common.size() + left.size());
            if (lratio >= SMALLMERGE_RATIO)
            {
                #if DEBUG_SMALLMERGE 
                cout << "smallmerge: " << i << " into " << j << " (ratio=" << lratio << ")" << endl;
                printvec(classes[i], "  lhs");
                printvec(classes[j], "  rhs");
                #endif
                
                for(int k = 0;k < classes[j].size();++k)
                {
                    const string& word = (classes[j])[k];
                    if (!binary_search(classes[i].begin(), classes[i].end(), word))
                    {
                        classes[i].push_back(word);
                        sort(classes[i].begin(), classes[i].end());
                    }
                }
                
                classes[j].clear();

                --i;
                break;
                
                #if DEBUG_SMALLMERGE
                cout << "Post merge setup: " << endl;
                printvec(classes[i], "  lhs");
                printvec(classes[j], "  rhs");
                #endif         
            }

            double rratio = double(common.size()) / double(common.size() + right.size());
            if (rratio >= SMALLMERGE_RATIO)
            {
                #if DEBUG_SMALLMERGE 
                cout << "smallmerge: " << j << " into " << i << " (ratio=" << rratio << ")" << endl;
                printvec(classes[i], "  lhs");
                printvec(classes[j], "  rhs");
                #endif
                
                for(int k = 0;k < classes[j].size();++k)
                {
                    const string& word = (classes[j])[k];
                    if (!binary_search(classes[i].begin(), classes[i].end(), word))
                    {
                        classes[i].push_back(word);
                        sort(classes[i].begin(), classes[i].end());
                    }
                }
                
                classes[j].clear();

                --i;
                break;
                
                #if DEBUG_SMALLMERGE
                cout << "Post merge setup: " << endl;
                printvec(classes[i], "  lhs");
                printvec(classes[j], "  rhs");
                #endif         
            }
        }
    }

    
    for(int i = 0;i < classes.size();++i)
    {
        if (classes[i].size() > PITHY_FILTER)
        {
//            copy(classes[i].begin(), classes[i].end(),
//                    ostream_iterator<string>(cout, " "));
//            cout << endl;
            output.push_back(classes[i]);
        }
    }
}


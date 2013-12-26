#include "Arguments.h"
#include "SmallMerge.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <ctime>
#include <iterator>
using namespace std;

static void
makeName(string basename, int index, string& name)
{
    strstream ss;
    ss << basename;
    ss << index;
    ss >> name;
}


class OutputMeaningSet
{
    std::ostream& d_out;
    
    public:
        OutputMeaningSet(std::ostream& out) : d_out(out) { }

        void operator()(const MeaningSet& x)
        {
            copy(x.begin(), x.end(), 
                    ostream_iterator<string>(d_out, " "));
            d_out << '\n';
        }
};


int main(int argc, const char** argv)
{
    Arguments A(argc, argv);

    int block_size;
    string basename;
    A.get("--basename", basename, "processed");
    A.get("--size", block_size, 1000);
    A.get("--ratio", SMALLMERGE_RATIO, .5); 
    A.get("--pithy", PITHY_FILTER, 10);
    basename += ".";
 
    cout << "--basename: " << basename << endl;
    cout << "--size: " << block_size << endl;
    cout << "--ratio: " << SMALLMERGE_RATIO << endl;
    cout << "--pithy: " << PITHY_FILTER << endl;
    

    cout << "Generating meanings list..." << flush;
    MeaningFamily all_meanings;
    extractMeaningFamily(cin, all_meanings);
    cout << "Meanings list generated. (" << all_meanings.size() << " sets.)" << endl;

    cout << "There will be " << 
        ceil(double(all_meanings.size()) / block_size) << " blocks to process." << endl;
    
    int stage = 0;
    MeaningFamily::iterator start = all_meanings.begin();
    
    while(start != all_meanings.end())
    {
        cout << "Processing block " << stage << flush;
        time_t tstart = time(NULL);
        string filename;
        makeName(basename, stage++, filename);

        ofstream out(filename.c_str());

        MeaningFamily block;
        block.reserve(block_size);
        
        cout << "." << flush;
        
        MeaningFamily::iterator end = 
            (all_meanings.end() < (start + block_size)) 
                ? (all_meanings.end()) 
                : (start + block_size);
        
        copy(start, end, back_inserter(block));
        
        cout << "." << flush;
        
        MeaningFamily output;
        output.reserve(block.size());
        smallMerge(block, output);
        
        cout << "." << flush;
    
        for_each(output.begin(), output.end(), OutputMeaningSet(out));
        
        cout << "." << flush;

        if (end == all_meanings.end())
            start = all_meanings.end();
        else
            start = end + 1;
        
        time_t tend = time(NULL);
        
        cout << " done after " << (tend - tstart) << " seconds:  "  
            << MERGES << " merges, " 
            << SUBSETS << " subsets." << endl;
    }

    return 0;
}


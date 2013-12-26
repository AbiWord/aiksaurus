#include "Arguments.h"
#include "Meanings.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;

class WriteFile
{
    private:
        std::ostream& d_out;

        static vector<int> d_sizes;
        static int d_max, d_min;
        
    public:
        
        WriteFile(std::ostream& out) 
        : d_out(out) 
        {
        
        }
        
        void operator()(const pair<string, vector<int> >& x)
        {
            int size = x.second.size();
            
            if ((d_max < size) || (d_max == -1)) 
                d_max = size;
            
            if ((d_min > size) || (d_min == -1)) 
                d_min = size;
            
            d_sizes.push_back(size);
            
            d_out << x.first << " ";
            copy(x.second.begin(), x.second.end(), 
                    ostream_iterator<int>(d_out, " "));
            d_out << '\n';
        }

        
        void printSummary()
        {
            cout << "\tGenerating summary statistics..." << endl;
       
            double avg = 0;
            for(unsigned int i = 0;i < d_sizes.size();++i)
            {
                avg += double(d_sizes[i]) / double(d_sizes.size());
            }
            
            sort(d_sizes.begin(), d_sizes.end());
            
            cout << "\tMinimum links/word: " << d_min << endl;
            cout << "\tMaximum links/word: " << d_max << endl;
            cout << "\tAverage links/word: " << avg << endl;
            cout << "\tMedian: " << d_sizes[d_sizes.size() / 2] << endl;
        }
};

int WriteFile::d_max = -1;
int WriteFile::d_min = -1;
vector<int> WriteFile::d_sizes;

int main(int argc, const char** argv)
{
    Arguments A(argc, argv);

    string wfile, mfile, ofile;
    if (  (!A.get("--words", wfile, "")) ||
          (!A.get("--meanings", mfile, "")) ||
          (!A.get("--output", ofile, ""))  )
    {
        cerr << "Syntax: " << argv[0] << " --words=w --meanings=m --output=o" << endl;
        exit(1);
    }

    cout << "\tReading words file..." << endl;
    string s;
    map<string, vector<int> > words;
    ifstream win(wfile.c_str());

    while(win >> s)
       words.insert( make_pair(s, vector<int>()) ); 

    cout << "\tReading meanings file..." << endl;
    ifstream min(mfile.c_str());
    MeaningFamily meanings;
    extractMeaningFamily(min, meanings);

    cout << "\tLinking..." << endl;
    for(unsigned int i = 0;i < meanings.size();++i) 
    {
        for(unsigned int j = 0;j < meanings[i].size();++j)
            words[ (meanings[i])[j] ].push_back(i);
    }

    cout << "\tGenerating output..." << endl;
    ofstream out(ofile.c_str());
    WriteFile wf(out);
    for_each(words.begin(), words.end(), wf);
    wf.printSummary();
    
    return 0;
}

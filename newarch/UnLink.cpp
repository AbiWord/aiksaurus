#include "Meanings.h"
#include "FastSaurus.h"
#include <iostream>
#include <strstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

typedef vector<int> LinkList;
typedef pair<string, LinkList> lnode;
typedef vector<lnode> StrLinkList;
    
MeaningFamily meanings;

unsigned int MAX_SIZE;

class LLSorter
{
    public:
        bool operator()(const lnode& lhs, const lnode& rhs)
        {
            int lsize = lhs.second.size();
            int rsize = rhs.second.size();

            if (lsize == rsize)
               return lhs.first < rhs.first;
            
            else
               return lhs.second.size() < rhs.second.size();
        }   
};

class LLPrinter
{
    ostream& d_out;
    
    public:
        LLPrinter(ostream& out) : d_out(out) {}

        void operator()(const lnode& x)
        {
            if (x.second.size(x) > MAX_SIZE)
            {

            }


            
            d_out << x.first << ' ';
            copy(x.second.begin(), x.second.end(), 
                 ostream_iterator<int>(cout, " "));
            d_out << '\n';
        }
};


int main()
{
    cout << "Enter meanings file name (m.#): " << flush;
    string mfile; cin >> mfile;

    cout << "Enter linked words file name (link.#): " << flush;
    string lfile; cin >> lfile;
    
    cout << "Enter maximum links size: " << flush;
    cin >> MAX_SIZE;
    
    cout << "Reading meanings file..." << endl;
    ifstream min(mfile.c_str());
    extractMeaningFamily(min, meanings);

    
    cout << "Reading links file..." << endl;
    ifstream l_in(lfile.c_str());
    
    char buf[64000];
    StrLinkList words;
    
    while(l_in.getline(buf, 64000))
    {
        istrstream ss(buf);
        string s; ss >> s;

        int x; vector<int> ll;
        while(ss >> x)
        {
            ll.push_back(x);
        }

        words.push_back(make_pair(s, ll));
    }

    cout << "Done reading links file." << endl;

    for_each(words.begin(), words.end(), LLPrinter(cout));
    
    return 0;
}

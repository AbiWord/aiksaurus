#include <iostream>
#include <strstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

typedef vector<int> LinkList;
typedef pair<string, LinkList> lnode;
typedef vector<lnode> StrLinkList;

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
            d_out << x.first << ' ';
            copy(x.second.begin(), x.second.end(), 
                 ostream_iterator<int>(cout, " "));
            d_out << '\n';
        }
};

int main()
{
    char buf[64000];

    StrLinkList words;
    
    while(cin.getline(buf, 64000))
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

    sort(words.begin(), words.end(), LLSorter());

    for_each(words.begin(), words.end(), LLPrinter(cout));
    
    return 0;
}

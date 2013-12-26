#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <strstream>
#include <algorithm>

class insensitiveStringCompare
{
    public:
        bool operator()(string lhs, string rhs)
        {
            for(unsigned int i = 0;i < lhs.size();++i)
                lhs[i] = tolower(lhs[i]);
            for(unsigned int i = 0;i < rhs.size();++i)
                rhs[i] = tolower(rhs[i]);
            return lhs < rhs;
        }
};

int main()
{
    string s;
    
    set<string> words;
    
    while(cin >> s)
        words.insert(s);    
    
    vector<string> v;
    v.reserve(words.size());
    
    copy(words.begin(), words.end(), back_inserter(v));
    
    sort(v.begin(), v.end(), insensitiveStringCompare());
    copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\n"));

    return 0;
}

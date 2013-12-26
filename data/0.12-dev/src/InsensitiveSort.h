#ifndef INCLUDED_INSENSITIVE_SORTER_H
#define INCLUDED_INSENSITIVE_SORTER_H

#include <string>
#include <cstring>
using namespace std;

class InsensitiveSorter
{
    public:

        bool operator()(const string& lhs, const string& rhs)
        {
            int val = strcasecmp(lhs.c_str(), rhs.c_str());
            
            return (
                (val == 0) 
                    ? ( strcmp(lhs.c_str(), rhs.c_str()) < 0 )
                    : ( val < 0 )
            );
        }
};

inline void strReplace(string& s, char a, char b)
{
    for(unsigned i = 0;i < s.size();++i)
        if (s[i] == a)
            s[i] = b;
}

class InsensitiveSorterFW
{
    public:

        bool operator()(string lhs, string rhs)
        {
            strReplace(lhs, ' ', 0);
            strReplace(rhs, ' ', 0);
            
            int val = strcasecmp(lhs.c_str(), rhs.c_str());
            
            return (
                (val == 0) 
                    ? ( strcmp(lhs.c_str(), rhs.c_str()) < 0 )
                    : ( val < 0 )
            );
        }
};

#endif // INSENSITIVE_SORTER_H

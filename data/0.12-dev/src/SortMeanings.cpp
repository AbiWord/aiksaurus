#include "InsensitiveSort.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <strstream>
using namespace std;

int main()
{
    vector< vector<string> > lines;
    
    char buf[64000];
    while(cin.getline(buf, 64000))
    {
        istrstream ss(buf);

        string temp;
        vector<string> line;
        while(ss >> temp)
            line.push_back(temp);

        sort(line.begin(), line.end(), InsensitiveSorter());

        copy(line.begin(), line.end(), ostream_iterator<string>(cout, " "));
        cout << '\n';
    }
    
    return 0;
}

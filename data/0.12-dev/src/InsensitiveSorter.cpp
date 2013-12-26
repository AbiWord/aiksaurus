#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include "InsensitiveSort.h"
using namespace std;

int main()
{
    vector<string> lines;

    char buf[64000];
    while(cin.getline(buf, 64000))
    {
        lines.push_back(string(buf));
    }

    sort(lines.begin(), lines.end(), InsensitiveSorterFW());

    copy(lines.begin(), lines.end(), ostream_iterator<string>(cout, "\n"));

    return 0;  
}

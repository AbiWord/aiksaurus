#include <set>
#include <iostream>
#include <string>
#include <strstream>

int main()
{
    string s;
    
    set<string> words;
    
    while(cin >> s)
        words.insert(s);    

    copy(words.begin(), words.end(), ostream_iterator<string>(cout, "\n"));

    return 0;
}

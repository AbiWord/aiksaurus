#include <iostream>
#include <string>
#include "Arguments.h"

int main(int argc, const char** argv)
{
    Arguments A(argc, argv);

    unsigned int maxlen;
    A.get("--maxlen", maxlen, 30);

    string x;
    while(cin >> x)
    {
        if (x.size() > maxlen)
            cout << x << endl;
    }

    return 0;
}

#include <iostream>

int main()
{
    char buf[64000];
    while(cin.getline(buf, 64000))
    {
        if (buf[0] == '#')
            continue;
        cout << buf << '\n';
    }
    
    return 0;
}

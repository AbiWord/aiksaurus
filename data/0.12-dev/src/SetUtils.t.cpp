#include "SetUtils.h"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;

int main()
{
    vector<int> a, b;

    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    a.push_back(6);
    a.push_back(7);
    a.push_back(8);
    a.push_back(9);
    a.push_back(10);

    b.push_back(1);
    b.push_back(2);
    b.push_back(3);
    b.push_back(4);
    b.push_back(5);

    vector<int> l;
    vector<int> r;
    vector<int> c;

    set_comparison(l, r, c, a.begin(), a.end(), b.begin(), b.end());
    cout << "set_comparison(a, b):\n";
    cout << " l = "; copy(l.begin(), l.end(), ostream_iterator<int>(cout, ", "));
    cout << "\n r = "; copy(r.begin(), r.end(), ostream_iterator<int>(cout, ", "));
    cout << "\n c = "; copy(c.begin(), c.end(), ostream_iterator<int>(cout, ", "));

    cout << endl << endl;
    
    l.clear();
    r.clear();
    c.clear();

    set_comparison(l, r, c, b.begin(), b.end(), a.begin(), a.end());
    cout << "set_comparison(b, a):\n";
    cout << " l = "; copy(l.begin(), l.end(), ostream_iterator<int>(cout, ", "));
    cout << "\n r = "; copy(r.begin(), r.end(), ostream_iterator<int>(cout, ", "));
    cout << "\n c = "; copy(c.begin(), c.end(), ostream_iterator<int>(cout, ", "));




    return 0;
}

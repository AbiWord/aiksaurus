#include <vector>
#include <iostream>
using namespace std;

//
// setCompare
// ----------
//   input:  two sorted vector<T>, references to return vectors.
//   return: 'left' will contain elements unique to lhs.
//           'right' will contain elements unique to rhs.
//           'same' will contain elements common to both.
//
template<class T>
void setCompare(
        vector<T>& left, 
        vector<T>& right, 
        vector<T>& same, 
        vector<T>& lhs, 
        vector<T>& rhs)
{
    int a = 0, b = 0;
       
    while((a < lhs.size()) && (b < rhs.size()))
    {
        if (lhs[a] < rhs[b]) 
        {
            left.push_back(lhs[a]);
            ++a; 
        }
        else if (lhs[a] == rhs[b])
        {
            same.push_back(lhs[a]);
            ++a;
            ++b;
        }
        else // lhs[a] > rhs[b]
        {
            right.push_back(lhs[a]);
            ++b;
        }
    }
    
    for(; a < lhs.size();++a)
    {
        left.push_back(lhs[a]);
    }
    
    for(; b < rhs.size(); ++b)
    {
        right.push_back(rhs[b]);
    }
}

int main()
{
    vector<int> a, b, c;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    a.push_back(6);

    b.push_back(2);
    b.push_back(4);
    b.push_back(6);

    c.push_back(1);
    c.push_back(3);
    c.push_back(5);

    vector<int> left, right, same;

    cout << "setCompare(a, a): " << endl;
    setCompare(left, right, same, a, a);
    cout << "left = " << left << ", right = " << right << ", same = " << same << endl;
    left.erase(left.begin(), left.end());
    right.erase(left.begin(), r

    cout << "setCompare(a, b): " << endl;
    setCompare(left, right, same, a, b);
    cout << "left = " << left << ", right = " << right << ", same = " << same << endl;
    cout << "setCompare(a, c): " << endl;
    setCompare(left, right, same, a, c);
    cout << "left = " << left << ", right = " << right << ", same = " << same << endl;
    
    cout << "setCompare(b, a): " << endl;
    setCompare(left, right, same, b, a);
    cout << "left = " << left << ", right = " << right << ", same = " << same << endl;
    cout << "setCompare(b, b): " << endl;
    setCompare(left, right, same, b, b);
    cout << "left = " << left << ", right = " << right << ", same = " << same << endl;
    cout << "setCompare(b, c): " << endl;
    setCompare(left, right, same, b, c);
    cout << "left = " << left << ", right = " << right << ", same = " << same << endl;
    
    cout << "setCompare(c, a): " << endl;
    setCompare(left, right, same, c, a);
    cout << "left = " << left << ", right = " << right << ", same = " << same << endl;
    cout << "setCompare(c, b): " << endl;
    setCompare(left, right, same, c, b);
    cout << "left = " << left << ", right = " << right << ", same = " << same << endl;
    cout << "setCompare(c, c): " << endl;
    setCompare(left, right, same, c, c);
    cout << "left = " << left << ", right = " << right << ", same = " << same << endl;
    
    return 0;
}





#include "AiksaurusGTK_utils.h"
#include <iostream>
#include <string>
using namespace std;


int main()
{
	cout << "Insert integer: " << flush;
	int x; cin >> x;

	char* y = AiksaurusGTK_intToString(x);
	
	cout << "String is: \n|" << y << "|" << endl;
	
	cout << "Enter string: " << flush;
	string a; cin >> a;

	char* foo = AiksaurusGTK_strConcat(a.c_str(), y);
	cout << "foo is " << foo << endl;

	delete[] y;
	delete[] foo;
	
	return 0;
}

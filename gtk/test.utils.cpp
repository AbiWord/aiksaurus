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
	
	return 0;
}

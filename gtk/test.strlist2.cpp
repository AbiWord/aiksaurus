#include "AiksaurusGTK_strlist.h"
#include <iostream>
using namespace std;


int main()
{
	cout << "Memory leak testing.  Check 'top' for memory leaks." << endl;
	
	cout << "Entering phase 1." << endl;
	AiksaurusGTK_strlist foo;
/*	for(int i = 0;i < 100000;++i)
	{
		for(int j = 0;j < 100;++j)
			foo.push_back("foo");

		for(int j = 0;j < 100;++j)
			foo.remove_last_element();
	}
*/
	cout << "Entering phase 2." << endl;
	for(int i = 0;i < 100000;++i)
	{
		AiksaurusGTK_strlist foo2;
	
		for(int j = 0;j < 100;++j)
			foo2.push_back("foo");
	
		// see if destructor gets this memory.
	}

	cout << "Entering phase 3." << endl;
	for(int i = 0;i < 100000;++i)
	{
		foo.push_back("foo2");
		foo.push_back("foo");
		foo.push_back("foo3");
		foo.remove_first("foo");
		foo.remove_first("foo2");
		foo.remove_first("foo3");
	}

	cout << "Entering phase 4." << endl;
	for(int i = 0;i < 100000;++i)
	{
		foo.push_back("foo");
		foo.push_back("foo2");
		foo.push_back("foo3");
		foo.push_front("foo4");
		foo.push_front("foo5");
		foo.push_front("foo6");
		foo.remove_last_element();
		foo.remove_last_element();
		foo.remove_last_element();
		foo.remove_last_element();
		foo.remove_last_element();
		foo.remove_last_element();
	}
	
	return 0;
}

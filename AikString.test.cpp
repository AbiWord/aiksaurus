#include <iostream>
#include "AikString.h"

int main()
{
	cout << "This is a series of simple tests of the AikString class.\n"  
		"If any of these tests fail, please notify aiken@clan11.com" << endl << endl;
	
	AikString test1("This is a test.");
	cout << "You should see: This is a test." << endl;
	cout << test1.c_str() << endl << endl;
	
	AikString test2("This is also a test.");
	cout << "You should see: This is also a test." << endl;
	cout << test2.c_str() << endl << endl;

	cout << "You should see: 15" << endl;
	cout << test1.size() << endl << endl;

	cout << "You should see: 20" << endl;
	cout << test2.size() << endl << endl;
	
	test1 = "This is yet another test.";
	cout << "You should see: This is yet another test." << endl;
	cout << test1.c_str() << endl << endl;

	cout << "You should see: 25" << endl;
	cout << test1.size() << endl << endl;

	test2 = test1;

	cout << "You should see: This is yet another test." << endl;
	cout << test2.c_str() << endl << endl;

	cout << "You should see: 25" << endl;
	cout << test2.size() << endl << endl;

	AikString test3("XXXXX");
	cout << "You should see: XXXXX" << endl;
	cout << test3.c_str() << endl << endl;

	test3.replaceAll('X', 'Y');
	cout << "You should see: YYYYY" << endl;
	cout << test3.c_str() << endl << endl;
	
	cout << "You should see: 1" << endl;
	cout << (test3 != test2) << endl << endl;

	cout << "You should see: 1" << endl;
	cout << (test2 == test1) << endl << endl;

	cout << "You should see: 0" << endl;
	cout << (test2 != test1) << endl << endl;

	AikString num1("12345");
	num1 += "67890";

	cout << "You should see: 1234567890" << endl;
	cout << num1.c_str() << endl << endl;

	cout << "You should see: 10" << endl;
	cout << num1.size() << endl << endl;
	
	num1 += num1;
	
	cout << "You should see: 12345678901234567890" << endl;
	cout << num1.c_str() << endl << endl;

	cout << "You should see: 20" << endl;
	cout << num1.size() << endl << endl;
	
	return 0;
}

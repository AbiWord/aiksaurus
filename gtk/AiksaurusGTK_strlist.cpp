#include "AiksaurusGTK_strlist.h"
#include <cstring>

#ifndef NDEBUG

#include <iostream>
using namespace std;

#endif // NDEBUG




static 
char* copyString(const char* str)
{	
	char* ret;
	
	if (str == NULL)
	{
		ret = new char[1];
		ret[0] = '\0';
	}

	else
	{
		const int len = strlen(str);

		ret = new char[len+1];
	
		for(register int i = 0;i < len;++i)
		{
			ret[i] = str[i];
		}

		ret[len] = '\0';
	}

	return ret;
}

static
void destroyString(void* str, gpointer data)
{
	char* x = static_cast<char*>(str);
	delete[] x;
}


AiksaurusGTK_strlist::AiksaurusGTK_strlist()
{
	d_list_ptr = NULL;
}


AiksaurusGTK_strlist::~AiksaurusGTK_strlist()
{
	g_list_foreach(d_list_ptr, destroyString, NULL);
	g_list_free(d_list_ptr);
}


void AiksaurusGTK_strlist::push_back(const char* str)
{
	char* x = copyString(str);
	d_list_ptr = g_list_append(d_list_ptr, x);
}


void AiksaurusGTK_strlist::push_front(const char* str)
{
	cout << "push_front(" << str << "):" << endl;
	char* x = copyString(str);
	cout << "  pushing " << x << endl;
	d_list_ptr = g_list_prepend(d_list_ptr, x);
	debug();
}

GList* AiksaurusGTK_strlist::getList()
{
	return d_list_ptr;
}



#ifndef NDEBUG

static 
void debugHelper(void* str, void* data)
{
	char* x = static_cast<char*>(str);
	cout << "   " << x << endl;
}

void AiksaurusGTK_strlist::debug()
{
	cout << "AiksaurusGTK_strlist::debug(): " << endl;
	cout << " Address of d_list_ptr is: " << d_list_ptr << endl;
	cout << " Contents of d_list_ptr are: " << endl;
	g_list_foreach(d_list_ptr, debugHelper, NULL);
}

#endif // NDEBUG



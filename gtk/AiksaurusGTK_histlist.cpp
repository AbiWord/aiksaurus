#include "AiksaurusGTK_histlist.h"
#include "AiksaurusGTK_strlist.h"


AiksaurusGTK_histlist::AiksaurusGTK_histlist(unsigned int maxElements)
{
	d_maxElements = maxElements;
	d_list_ptr = new AiksaurusGTK_strlist;
}


AiksaurusGTK_histlist::~AiksaurusGTK_histlist()
{
	delete d_list_ptr;
}


void AiksaurusGTK_histlist::addItem(const char* str)
{
	d_list_ptr->remove_first(str);
	d_list_ptr->push_front(str);

	if (d_list_ptr->size() > d_maxElements)
	{
		d_list_ptr->remove_last_element();
	}
}


const GList* AiksaurusGTK_histlist::list() const
{
	return d_list_ptr->list();
}



#ifndef NDEBUG

#include <iostream>
using namespace std;

void AiksaurusGTK_histlist::debug()
{
	cout << "AiksaurusGTK_histlist::debug() {" << endl;
	cout << "  MaxElements is " << d_maxElements << endl;
	cout << "  List information follows: " << endl;
	d_list_ptr->debug();
	cout << "}" << endl;
}

#endif // NDEBUG


#ifndef INCLUDED_JARED_GPL_AIKSAURUSGTK_STRLIST_H
#define INCLUDED_JARED_GPL_AIKSAURUSGTK_STRLIST_H

#include <glib.h>

//
// AiksaurusGTK_strlist class
// --------------------------
//   This is a wrapper for the GList class which provides string copying
//   features so that you can add strings and store them directly in the list
//   with a minimum of fuss.
//
//   In other words, when you push_back() or push_front() strings to this list,
//   a copy of the string will be put in the list.  This makes it much easier 
//   to reuse pointers and so forth, and you don't have to remember to delete 
//   the strings you've added because the destructor does it for you.
//   

class AiksaurusGTK_strlist
{
	private:
	
		GList* d_list_ptr;

	public:

		AiksaurusGTK_strlist();
		~AiksaurusGTK_strlist();
		
		void push_back(const char* str);
		void push_front(const char* str);

		GList* getList();

		#ifndef NDEBUG
		void debug();
		#endif
};

#endif // INCLUDED_JARED_GPL_AIKSAURUSGTK_STRLIST_H

#ifndef INCLUDED_JARED_GPL_AIKSAURUSGTK_HISTORYLIST_H
#define INCLUDED_JARED_GPL_AIKSAURUSGTK_HISTORYLIST_H

#include <glib.h>

class AiksaurusGTK_strlist;
class AiksaurusGTK_histlist
{
	private:

		AiksaurusGTK_strlist* d_list_ptr;
		unsigned int d_maxElements;
		
		// Prevent copying and assignment.
		AiksaurusGTK_histlist(const AiksaurusGTK_histlist& rhs);
		const AiksaurusGTK_histlist& operator=(const AiksaurusGTK_histlist& rhs);
		
	public:

		AiksaurusGTK_histlist(unsigned int maxElements);
		~AiksaurusGTK_histlist();

		void addItem(const char* str);

		const GList* list() const;	

		#ifndef NDEBUG
		void debug();
		#endif // NDEBUG
};


#endif // INCLUDED_JARED_GPL_AIKSAURUSGTK_HISTLIST_H

#ifndef INCLUDED_JARED_GPL_AIKSAURUSGTK_UTILS_H
#define INCLUDED_JARED_GPL_AIKSAURUSGTK_UTILS_H

//
// AiksaurusGTK_strEquals
// ----------------------
//   Returns true if lhs == rhs, false otherwise.
//   
bool AiksaurusGTK_strEquals(const char* lhs, const char* rhs);


//
// AiksaurusGTK_strCopy
// --------------------
//   Creates a copy of the string str.  This copy must be 
//   delete[]'d by the caller, so use this function carefully.
//   
char* AiksaurusGTK_strCopy(const char* str);


#endif // INCLUDED_JARED_GPL_AIKSAURUSGTK_UTILS_H

#ifndef INCLUDED_JARED_GPL_GTKAIKSAUR_H
#define INCLUDED_JARED_GPL_GTKAIKSAUR_H

//
// ActivateThesaurus
// -----------------
//   
//   Arguments:
//
//     Takes a character pointer to a string that the user wants to search 
//     for.  Usually this is whatever word their cursor is over, or whatever 
//     word is selected when the user activates the thesaurus dialog.
//
//     If there is no word, you can safely pass either a blank string ("") 
//     or you can pass NULL and it will be interpreted as a blank string.
//  
//  
//   Return Value:
//   
//     A character pointer to a (possibly) new word that the user wants to 
//     replace the word they searched for with.
//     
//     Note: you should not attempt to delete/free the returned string 
//     yourself.
//   
const char* ActivateThesaurus(const char* search);

#endif // INCLUDED_JARED_GPL_GTKAIKSAUR_H

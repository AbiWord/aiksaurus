#ifndef INCLUDED_SMALLMERGE_H
#define INCLUDED_SMALLMERGE_H

#include "Meanings.h"


// SMALLMERGE_RATIO 
//   Smallmerge will merge any set that has at least this percent of 
//   its synonyms in common with another set.
extern double SMALLMERGE_RATIO;


// PITHY_FILTER 
//   Smallmege will remove all meaning sets with less than this many 
//   elements.
extern unsigned int PITHY_FILTER;

// amount of eliminations.
extern unsigned int SUBSETS;
extern unsigned int MERGES;

// smallMerge
//
//   "classes" is a family of meanings to merge.  this object will
//   get butchered in the process of a smallmerge, and will contain 
//   many blank elements afterwards.
//
//   "output" is where merged output will be put into a nice, new 
//   meaning family.
//
void smallMerge(MeaningFamily& classes, MeaningFamily& output);


#endif // INCLUDED_SMALLMERGE_H

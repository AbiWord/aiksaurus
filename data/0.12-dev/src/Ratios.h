#ifndef INCLUDED_RATIOS_H
#define INCLUDED_RATIOS_H

#include "Meanings.h"
    
    double returnLinkRatio(const std::string& word, const MeaningSet& meanings);
    double directLinkRatio(const std::string& word, const MeaningSet& meanings);

    double meanReturnLinkRatio(const MeaningSet& meanings);
    double meanDirectLinkRatio(const MeaningSet& meanings);

#endif // INCLUDED_RATIOS_H

#ifndef INCLUDED_AIKSAURUS_MEANINGSTREAM_H
#define INCLUDED_AIKSAURUS_MEANINGSTREAM_H

#include <iostream>

class MeaningStream
{
    private:
 
    // Input stream to read from ------------------------------------
        
        std::istream& d_in;
        
    // No copying or assignment -------------------------------------
        
        MeaningStream(const MeaningStream& rhs);
        MeaningStream& operator=(const MeaningStream& rhs);
        
        
    public:
      
    // Creation and Destruction -------------------------------------
        
        MeaningStream(std::istream& stream);
        ~MeaningStream();
      
        
    // Manipulation -------------------------------------------------
        
        bool operator>>(int& id);
           

    // Public Constants ---------------------------------------------

       static const int EOL;    
};

#endif // INCLUDED_AIKSAURUS_MEANINGSTREAM_H

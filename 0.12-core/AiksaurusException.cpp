#include "AiksaurusException.h"     // Header we're implementing.
#include "config.h"                 // For AIK_DATA_DIR define.
#include <cassert>                  

namespace AiksaurusImpl
{
    const char* AiksaurusException::CANNOT_OPEN_MEANINGS_FILE = 
        "Error: Cannot Open Meanings File\n"
        "There has been a problem opening the file \"" 
        AIK_DATA_DIR 
        "meanings.dat\".\n"
        "This most likely indicates that the file has been "
        "moved or deleted.  If you cannot find the file, you "
        "can download a new copy from: \n"
        "   http://www.aiksaurus.com/_support/012/meanings.dat\n";

    const char* AiksaurusException::CANNOT_OPEN_WORDS_FILE =
        "Error: Cannot Open Words File\n"
        "There has been a problem opening the file \""
        AIK_DATA_DIR
        "words.dat\".\n"
        "This most likely indicates that the file has been "
        "moved or deleted.  If you cannot find the file, you "
        "can download a new copy from: \n"
        "   http://www.aiksaurus.com/_support/012/words.dat\n";

    const char* AiksaurusException::CORRUPT_MEANINGS_FILE = 
        "Error: Corrupt Meanings File\n"
        "There has been a problem reading the file \""
        AIK_DATA_DIR
        "meanings.dat\".\n"
        "The file exists, but was not read correctly.  Either "
        "the file has become corrupt or this is a bug. \n"
        "Please download a new copy of the file from: \n"
        "   http://www.aiksaurus.com/_support/012/meanings.dat\n"
        "If this does not fix the problem, please contact \n"
        "   jared@aiksaurus.com\n";

    const char* AiksaurusException::CORRUPT_WORDS_FILE = 
        "Error: Corrupt Words File\n"
        "There has been a problem reading the file \""
        AIK_DATA_DIR
        "words.dat\".\n"
        "The file exists, but was not read correctly.  Either "
        "the file has become corrupt or this is a bug. \n"
        "Please download a new copy of the file from: \n"
        "   http://www.aiksaurus.com/_support/012/words.dat\n"
        "If this does not fix the problem, please contact \n"
        "   jared@aiksaurus.com\n";

    const char* AiksaurusException::CANNOT_ALLOCATE_MEMORY = 
        "Error: Cannot Allocate Memory\n"
        "No memory was available for the Thesaurus.  You  "
        "could try closing some other programs to make more "
        "memory available.\n";


    AiksaurusException::AiksaurusException(const char* description) throw()
        : d_description(description)
    {
        assert(
            (d_description == CANNOT_OPEN_MEANINGS_FILE) ||
            (d_description == CORRUPT_MEANINGS_FILE) ||
            (d_description == CANNOT_OPEN_WORDS_FILE) ||
            (d_description == CORRUPT_WORDS_FILE) ||
            (d_description == CANNOT_ALLOCATE_MEMORY)
        );
    }

    
    AiksaurusException::~AiksaurusException() throw()
    {
    
    }


    const char* 
    AiksaurusException::getDescription() const throw()
    {
        return d_description;
    }
}

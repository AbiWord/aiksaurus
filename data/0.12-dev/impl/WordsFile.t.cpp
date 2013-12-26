#include "WordsFile.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace AiksaurusImpl;
int main()
{
    std::cout << "Enter input file: " << std::flush;
    std::string input; std::cin >> input;
 
    std::cout << "Enter output file: " << std::flush;
    std::string ofile; std::cin >> ofile;

    std::ofstream out(ofile.c_str());
   
    WordsFile wf(input.c_str());

    if (wf.getError().isError())
    {
        std::cerr << wf.getError().getDescription() << std::endl;
        return 1;
    }
    
    for(int i = 0;i < wf.getSize();++i)
    {
        wf.loadWord(i);

        if (wf.getError().isError())
        {
            std::cerr << wf.getError().getDescription() << std::endl;
            return 1;
        }
        
        out << wf.getWord() << ' ';

        const int* links = wf.getLinks();
        for(int i = 0; links[i] != -1;++i)
           out << links[i] << " ";
        out << '\n'; 
    }

    return 0;
}

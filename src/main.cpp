#include "parser.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        std::cout << argv[0] << ": missing file operand" << std::endl;
        return -1;
    }
    else
    {
        //attempt to read GD level string and find level data index
        std::string levelFile = readFile(argv[1]);
        if(levelFile.empty())
        {
            std::cout << "ERROR: Failed to open file (empty or does not exist)" << std::endl;
            return -1;
        }

        int beginIndex = getFirstObjIndex(levelFile);

        //initialize an Impossible Game level
        Level result(false);

        //valid level data must have been found
        if(beginIndex != -1)
        {
            //process and convert level data
            parseObjects(result, levelFile, beginIndex);
            BlockObject last = result.getBlockAtIndex(result.getBlockCount() - 1);
            std::cout << "Setting end position to x " << result.getEndPos() << std::endl;
            std::string fileName = argv[1];
            
            //remove ".txt" from the filepath and replace with ".lvl"
            for(int i = 0; i < 4; i++)
            {
                fileName.pop_back();
            }

            //write the level file
            fileName += ".lvl";
            result.saveLevel(fileName);
            writeDummyMP3(fileName);

            //print level summary
            result.printSummary();
        }
        else
        {
            std::cout << "ERROR: Failed to find object data in file (not a GD level string?)" << std::endl;
            std::cout << "Make sure that all the data is on a single line, and is fully decoded" << std::endl;
            return -1;
        }
    }

    return 0;
}
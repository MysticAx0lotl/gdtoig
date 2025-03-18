#include "parser.hpp"
#include "dummyMP3.hpp"

//Actual object data begins at the first semicolon, everything before that is level configuration data that is useless to TIG
//levelString: the raw level data from GD (passed by reference to avoid wasting memory)
//returns the index if found, otherwise returns -1
int getFirstObjIndex(std::string &levelString)
{
    for(int i = 0; i < levelString.size(); i++)
    {
        if(levelString[i] == ';')
        {
            std::cout << "Got character " << levelString[i] << " at " << i;
            return i;
        }
    }

    return -1;
}

//parses object data from a GD level string and writes it to a libImpossibleLevel level class
//igLevel: a properly initialized Level object (passed by reference)
//gdLevel: the raw level data from GD (passed by reference)
//startIndex: the character in the GD level string to start from (usually the return value of getFirstObject)
//returns: nothing
void parseObjects(Level &igLevel, std::string &gdLevel, int startIndex)
{
    //initialize values
    int currentID;
    int maxXPos = 0;
    int i = startIndex;
    std::string inBuf;
    std::string objectName;

    //create temporary object
    BlockObject *tempBlock = new BlockObject;
    tempBlock->xPos = 0;
    tempBlock->yPos = 0;
    tempBlock->objType = 0;
    tempBlock->indexInVec = 0;

    //gdLevel[i] is a semicolon, we want to skip past that
    i += 1;

    //iterate through the rest of the leveldata
    while(i < gdLevel.size())
    {
        inBuf.clear();

        //skip over the identifier for the object ID
        while(gdLevel[i] != ',')
        {
            i++;
        }
        i++;

        //get the object ID from the following chunk of data
        while(gdLevel[i] != ',')
        {
            if(gdLevel[i] != ',')
            {
                inBuf += gdLevel[i];
            }
            i++;
        }

        //output the contents of idBuf for debugging
        std::cout << "inbuf " << inBuf << std::endl;

        //write idBuf to currentID
        currentID = stoi(inBuf);

        objectName = "null";

        //This switch takes the IDs defined in compat_defs.hpp and maps them to Impossible Game equivalents
        switch(currentID)
        {
            case gd_decoblock:
                objectName = "block";
                break;
            case gd_defblock:
                objectName = "block";
                break;
            case gd_decocorner:
                objectName = "block";
                break;
            case gd_fulldecoblock:
                objectName = "block";
                break;
            case gd_decopipe:
                objectName = "block";
                break;
            case gd_decopipecap:
                objectName = "block";
                break;
            case gd_slab:
                objectName = "block";
                break;
            case gd_spike:
                objectName = "spike";
                break;
            case gd_pit:
                objectName = "pit";
                break;
            default:
                break;
        }

        //make sure the object being processed is actually defined
        if (objectName != "null")
        {
            //Parsing for the x and y positions work pretty much identically to parsing the level ID
            i += 3;
            inBuf.clear();
            while(gdLevel[i] != ',')
            {
                if(gdLevel[i] != ',')
                {
                    inBuf += gdLevel[i];
                }
                i++;
            }
            std::cout << "xposbuf " << inBuf << std::endl;
            tempBlock->xPos = (stoi(inBuf) + gd_xposoffset) * ig_xscale;

            //keeps track of the furthest-placed block (will be used to calculate the end wall position)
            if(tempBlock->xPos > maxXPos)
            {
                maxXPos = tempBlock->xPos;
            }
            i += 3;

            inBuf.clear();
            while(gdLevel[i] != ',')
            {
                if(gdLevel[i] != ',')
                {
                    inBuf += gdLevel[i];
                }
                i++;
            }
            std::cout << "yposbuf " << inBuf << std::endl;
            tempBlock->yPos = ((stoi(inBuf) - gd_yposoffset) * ig_scale);

            //quick and dirty fix to make certain jumps possible
            if(currentID == gd_slab)
            {
                tempBlock->yPos -= 15;
            }
            
            i += 2;
            inBuf.clear();

            //currently unused
            while(gdLevel[i] != ',')
            {
                if(gdLevel[i] != ',')
                {
                    inBuf += gdLevel[i];
                }
                i++;
            }
            std::cout << "rotbuf " << inBuf << std::endl;

            //set the correct object type
            //note: pits have no y position, just a start and end value
            if(objectName == "block"){tempBlock->objType = 0;}
            else if(objectName == "spike"){tempBlock->objType = 1;}
            else if(objectName == "pit"){tempBlock->objType = 2; tempBlock->yPos = tempBlock->xPos + 30;}


            igLevel.addBlock(tempBlock);
        }

        //skip to next object
        while(gdLevel[i] != ';')
        {
            i++;
        }

        i++;
        
    }

    //sets the end of the level 10 grid spaces from the furthest block
    igLevel.setEndPos(maxXPos + 300);

}

//copied pretty much verbatim from cplusplus.com
std::string readFile(char *loadFile)
{
    std::string result;
    std::ifstream myfile (loadFile);
    if (myfile.is_open())
    {
        getline (myfile,result);
        myfile.close();
    }

    return result;
}

//The Impossible Game requires a file named music.mp3 to be present to successfully load a custom level
//This function writes a dummy MP3 (defined in dummyMP3.hpp) to the level folder, which can later be replaced
//outDir: the folder that the mp3 will be written to
void writeDummyMP3(std::string outDir)
{
    if(!std::filesystem::exists(outDir))
    {
        return;
    }

    outDir += "/music.mp3";

    std::ofstream dataOut;
    dataOut.open(outDir.c_str(), std::ios_base::binary | std::ios_base::out);
    dataOut.write(reinterpret_cast<const char*>(dummyMP3), 625);
}
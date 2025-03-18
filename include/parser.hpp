#ifndef FILE_PARSER
#define FILE_PARSER

#include "compat_defs.hpp"
#include "libImpossibleLevel.hpp"
#include <fstream>
#include <string>

//NOTE: All functions are commented in parser.cpp

int getFirstObjIndex(std::string &levelString);

void parseObjects(Level &igLevel, std::string &gdLevel, int startIndex);

std::string readFile(char *loadFile);

void writeDummyMP3(std::string outDir);

#endif
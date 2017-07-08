#include "Loader.h"

#include <stdexcept>

#include "STD_Util.h"

void Loader::load(const std::string name)
{
    std::ifstream inFile (name);
    if (!inFile.is_open())
    {
        throw std::runtime_error ("Unable to load file: " + name);
    }

    std::string line;
    while(std::getline(inFile, line))
    {
        if(isEmptyLine(line))
        {
            continue;
        }
        else if (!parseLine(line, inFile))
        {
            throw std::runtime_error("Unrecognised token \"" + line + "\" in " + name);
        }
    }
}

bool Loader::isEmptyLine(std::string& line) const
{
    return  areStringsSame(line, ""  ) ||
            areStringsSame(line, " " ) ||
            areStringsSame(line, "\t");
}



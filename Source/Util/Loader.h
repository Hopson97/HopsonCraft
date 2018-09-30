#ifndef LOADER_H_INCLUDED
#define LOADER_H_INCLUDED

#include <fstream>
#include <string>

class Loader
{
    protected:
        void load(const std::string name);

    private:
        virtual bool parseLine(const std::string& line, std::ifstream& inFile) = 0;

    private:
        bool isEmptyLine(std::string& line) const;
};

#endif // LOADER_H_INCLUDED

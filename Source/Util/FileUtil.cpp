#include "FileUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>


#include <filesystem>

/**
    Because this uses experimental file-system lib (At this time,
    I can't seem to get GCC 7 to download), you must add compiler option:

    -lstdc++fs
*/
    namespace FS = std::filesystem;

    using Path      = FS::path;
    using DirItr    = FS::directory_iterator;

std::string getFileContents(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    std::stringstream stream;

    stream << inFile.rdbuf();   //Gets the file contents into a string stream
    return stream.str();        //Return the string from the string stream
}

std::vector<std::string> getFilePathsFromFolder(const std::string& folderName)
{
    std::vector<std::string> fileNames;

    for (auto& entry : DirItr(folderName))
    {
        if (FS::is_regular_file(entry))
        {
            fileNames.emplace_back(Path(entry));
        }
    }

    return fileNames;
}
























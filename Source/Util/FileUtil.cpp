#include "FileUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <experimental/filesystem>

#include "Native.h"


namespace FS = std::experimental::filesystem;

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
        if (std::experimental::filesystem::is_regular_file(entry))
        {
            fileNames.push_back(Path(entry));
            std::cout << Path(entry);
        }
    }

    return fileNames;
}























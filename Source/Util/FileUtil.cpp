#include "FileUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "Native.h"

std::string getFileContents(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    std::stringstream stream;

    stream << inFile.rdbuf();   //Gets the file contents into a string stream
    return stream.str();        //Return the string from the string stream
}




#ifdef __WIN32
    std::vector<std::string> getFileNamesFromFolder(const std::string& folderName)
    {
        std::vector<std::string> fileNames;
        std::string searchFor (folderName + "/*.*");
        WIN32_FIND_DATA findData;
        auto hFind = ::FindFirstFile(searchFor.c_str(), &findData);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if(!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                {
                    fileNames.push_back(findData.cFileName);
                }

            } while (::FindNextFile(hFind, &findData));
        }

        return fileNames;
    }
/*
    ///@TODO Linux/ etc of this
    std::vector<std::string> getFolderNamesFromFolder(const std::string& folderName)
    {
        std::vector<std::string> folderNames;

        WIN32_FIND_DATA findData;
        auto hFind = INVALID_HANDLE_VALUE;



    }
*/

#elif __linux__ || __APPLE__
    std::vector<std::string> getFileNamesFromFolder(const std::string& folderName)
    {
        return {};
        std::vector<std::string> fileNames;
        DIR* directory = opendir(folderName.c_str());
        dirent* dir;

        if (directory)
        {
            while ((dir = readdir(directory)) != nullptr)
            {
                fileNames.push_back(dir->d_name);
            }
        }
        closedir(directory);
        return fileNames;

    }
#endif
























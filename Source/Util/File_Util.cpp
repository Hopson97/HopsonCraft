#include "File_Util.h"

#include <fstream>
#include <sstream>

#ifdef __WIN32
    #include <windows.h>
#endif // __WIN32

namespace
{
    #ifdef __WIN32
    std::vector<std::string> getFileNamesFromFolderLocal(const std::string& folderName)
    {
        #ifdef __WIN32
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
        #endif // __WIN32
    }
    #endif // __WIN32
}


std::string getFileContents(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    std::stringstream stream;

    stream << inFile.rdbuf();   //Gets the file contents into a string stream
    return stream.str();        //Return the string from the string stream
}

#ifdef __WIN32
///@TODO More OS implementations of this function
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

#else

std::vector<std::string> getFileNamesFromFolder(const std::string& folderName)
{
    return {};
}

#endif






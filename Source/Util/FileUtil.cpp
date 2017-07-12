#include "FileUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>

#ifdef __linux__ || __APPLE__
    #include <experimental/filesystem>

/**
    Because this uses experimental file-system lib (At this time,
    I can't seem to get GCC 7 to download), you must add compiler option:

    -lstdc++fs
*/
    namespace FS = std::experimental::filesystem;

    using Path      = FS::path;
    using DirItr    = FS::directory_iterator;
#else
    #include <windows.h>
#endif

std::string getFileContents(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    std::stringstream stream;

    stream << inFile.rdbuf();   //Gets the file contents into a string stream
    return stream.str();        //Return the string from the string stream
}


#ifdef __WIN32
    std::vector<std::string> getFilePathsFromFolder(const std::string& folderName)
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
                    fileNames.push_back(folderName + "/" + findData.cFileName);
                }

            } while (::FindNextFile(hFind, &findData));
        }

        return fileNames;
}

#elif __linux__ || __APPLE__

std::vector<std::string> getFilePathsFromFolder(const std::string& folderName)
{
    std::vector<std::string> fileNames;

    for (auto& entry : DirItr(folderName))
    {
        if (FS::is_regular_file(entry))
        {
            fileNames.push_back(Path(entry));
        }
    }

    return fileNames;
}

#endif // __WIN32























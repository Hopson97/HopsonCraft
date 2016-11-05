#include "Directory_Creator.h"

#ifdef linux
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
#elif _WIN32
    #include <windows.h>
#endif

namespace Directory
{
    void create(const std::string& folderName)
    {
        #ifdef linux
            mkdir(folderName.c_str(), 0700);
        #elif _WIN32
            CreateDirectory(folderName.c_str(), nullptr);
        #endif
    }
}

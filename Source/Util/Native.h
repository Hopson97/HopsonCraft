#ifndef NATIVE_H_INCLUDED
#define NATIVE_H_INCLUDED

#ifdef __WIN32
    #include <windows.h>
#elif __linux__ || __APPLE__
    #include <sys/types.h>
    #include <dirent.h>
#endif // __linux__

#endif // NATIVE_H_INCLUDED

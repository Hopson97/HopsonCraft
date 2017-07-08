#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

//#define DEBUG_MODE

#ifdef DEBUG_MODE
    #define LOG(format, ...)        \
    {                               \
        printf(format, ##__VA_ARGS__);\
    }

#else
    #define LOG(...){}
#endif // LOG

#endif // LOG_H_INCLUDED

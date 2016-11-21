#include "Time.h"

#include <ctime>

namespace Time
{
    std::tm* getTime()
    {
        std::time_t theTime = std::time(0);
        std::tm* now = std::localtime(&theTime);

        return now;
    }

    std::string getTimeString()
    {
        auto now = getTime();

        auto hour   = now->tm_hour;
        auto minute = now->tm_min;
        auto second = now->tm_sec;

        return  std::to_string (hour)   + ":" +
                std::to_string (minute) + ":" +
                std::to_string (second) + " ";

    }

    std::string getDateString()
    {
        auto now = getTime();

            auto year   = now->tm_year  + 1900;
            auto month  = now->tm_mon   + 1;
            auto day    = now->tm_mday;

        return  std::to_string (day)   + "/" +
                std::to_string (month)  + "/" +
                std::to_string (year)    + " ";
    }
}

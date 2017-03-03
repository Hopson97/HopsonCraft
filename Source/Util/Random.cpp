#include "Random.h"

#include <random>
#include <ctime>

namespace Random
{
    namespace
    {
        std::minstd_rand rd;
    }

    void init()
    {
        rd.seed(std::time(nullptr));
    }

    int intInRange(int lowBound, int highBound)
    {
        std::uniform_int_distribution<int> dist(lowBound, highBound);
        return dist (rd);
    }

}

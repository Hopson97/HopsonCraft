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
}

#include "Random.h"

namespace Random
{
    namespace
    {
        std::mt19937 rd;
    }

    void init()
    {
        rd.seed(std::time(nullptr));
    }

    int64_t intInRange(int64_t lowBound, int64_t highBound)
    {
        std::uniform_int_distribution<int64_t> dist(lowBound, highBound);
        return dist (rd);
    }
}

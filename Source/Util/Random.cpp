#include "Random.h"

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <random>
#include <mutex>

namespace Random
{
    std::minstd_rand gen;

/*
	int integer(int low, int high)
	{
		return rand() % (high - low + 1) + low;
	}

	double decimalD( double low, double high, int precision )
	{
		double multiplier = pow(10, precision);

		low *= multiplier;
		high *= multiplier;

		double newNum = integer(low, high);

		return newNum / multiplier;
	}
*/
    void setSeed(int seed)
    {
        gen.seed(seed);
    }


    int integer(int low, int high)
    {
        std::uniform_int_distribution<int> dist(low, high);
        return dist(gen);
    }

    double decimal(double low, double high)
    {
        std::uniform_real_distribution<double> dist(low, high);
        return dist(gen);
    }
}

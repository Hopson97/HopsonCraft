#include "random.h"

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <random>
#include <mutex>

namespace Random
{

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

    void setSeed(int seed)
    {
        srand(seed);
    }

    Generator::Generator()
    {
        m_rng.seed(std::random_device()());
    }

    void Generator::setSeed(int value)
    {
        m_rng.seed(value);
    }

    int Generator::get(int low, int high)
    {
        std::uniform_int_distribution<std::mt19937::result_type> distribution(low, high);
        return distribution(m_rng);
    }



}

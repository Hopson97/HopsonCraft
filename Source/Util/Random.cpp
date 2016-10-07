#include "random.h"

#include <ctime>
#include <cstdlib>
#include <cmath>

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

}
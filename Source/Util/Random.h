#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <random>

namespace Random
{
	int integer		( int low, int high );

	double decimalD ( double low, double high, int precision = 1 );

	void setSeed (int seed);
}

#endif

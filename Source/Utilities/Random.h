#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

namespace Random
{
	int integer		( int low, int high );

	double decimal ( double low, double high, int precision = 1 );
}

#endif

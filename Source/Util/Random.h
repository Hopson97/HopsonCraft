#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <random>

namespace Random
{
	int integer		( int low, int high );

	double decimalD ( double low, double high, int precision = 1 );

	void setSeed (int seed);

	class Generator
	{
        public:
            Generator();
            void setSeed (int value);
            int get(int low, int high);

        private:
            std::mt19937 m_rng;
	};
}

#endif

#ifndef BWATER_H_INCLUDED
#define BWATER_H_INCLUDED

#include "Block_Type.h"

namespace Block
{
    class BWater : public Type
    {
        public:
            BWater();
            void trigger(World& world, const Position& position) const;

        private:
            bool tryMove(World& world, const Position& position, const Position& vect) const;
    };
}

#endif // BWATER_H_INCLUDED

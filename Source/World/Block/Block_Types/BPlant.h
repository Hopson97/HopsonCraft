#ifndef BPLANT_H_INCLUDED
#define BPLANT_H_INCLUDED

#include "Block_Type.h"

namespace Block
{
    class BPlant : public Type
    {
        public:
            BPlant(const std::string& name);
            void trigger(World& world, const Position& position) const;
    };
}

#endif // BPLANT_H_INCLUDED

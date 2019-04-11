#ifndef BPLANT_H_INCLUDED
#define BPLANT_H_INCLUDED

#include "BlockType.h"

namespace Block
{
    class BPlant : public Type
    {
        public:
            BPlant(std::string&& name);
            void trigger(World& world, CBlock& block, const Position& position) const override;
    };
}

#endif // BPLANT_H_INCLUDED

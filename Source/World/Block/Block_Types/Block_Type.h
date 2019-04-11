#ifndef BLOCK_TYPE_H
#define BLOCK_TYPE_H

#include <string>

#include "../Block_Data.h"
#include "../Block_Position.h"

class World;
class CBlock;

namespace Block
{
    class Type
    {
        public:
            const Data& getData() const;

            virtual void tick   (World& world, CBlock& block, const Position& position) const{}
            virtual void trigger(World& world, CBlock& block, const Position& position) const{}

        protected:
            Type(std::string&& fileName);

        private:
            Data m_data;
    };
}

#endif // BLOCK_TYPE_H

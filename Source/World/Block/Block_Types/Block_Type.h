#ifndef BLOCK_TYPE_H
#define BLOCK_TYPE_H

#include <string>

#include "../Block_Data.h"
#include "../Block_Position.h"

class World;

namespace Block
{
    class Type
    {
        public:
            const Data& getData() const;

            virtual void tick   (World& world, const Position& position){}
            virtual void trigger(World& world, const Position& position){}

        protected:
            Type(const std::string& fileName);

        private:
            Data m_data;
    };
}

#endif // BLOCK_TYPE_H

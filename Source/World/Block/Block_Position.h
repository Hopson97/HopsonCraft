#ifndef BLOCK_POSITION_H_INCLUDED
#define BLOCK_POSITION_H_INCLUDED

#include <cstdint>
#include <SFML/System/Vector3.hpp>

#include "../../Util/Hasher.h"

namespace Block
{
    typedef sf::Vector3<int8_t>  Small_Position;
    typedef sf::Vector3<int32_t> Position;
}

namespace std
{
    template<>
    struct hash<Block::Small_Position>
    {
        size_t operator() (const Block::Small_Position& pos) const
        {
            return Hasher::hash(pos.x, pos.y, pos.z);
        }
    };
}

#endif // BLOCK_POSITION_H_INCLUDED

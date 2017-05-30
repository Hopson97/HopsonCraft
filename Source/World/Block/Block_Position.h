#ifndef BLOCK_POSITION_H_INCLUDED
#define BLOCK_POSITION_H_INCLUDED

#include <cstdint>
#include <SFML/System/Vector3.hpp>

#include "../../Util/Hasher.h"

namespace Block
{
    //typedef sf::Vector3<int8_t>  Position;
    typedef sf::Vector3<int> Position;
}
/*
namespace std
{
    template<>
    struct hash<Block::Position>
    {
        size_t operator() (const Block::Position& pos) const
        {
            return Hasher::hash(pos.x, pos.y, pos.z);
        }
    };
}
*/
#endif // BLOCK_POSITION_H_INCLUDED

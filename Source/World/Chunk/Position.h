#ifndef CPOSITION_H_INCLUDED
#define CPOSITION_H_INCLUDED

#include <functional>
#include <cstdint>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../Util/Hasher.h"
#include "../Block/Block_Position.h"

namespace Chunk
{
    typedef sf::Vector3<int32_t> Chunklet_Position;
    typedef sf::Vector2<int32_t> Position;
}

namespace std
{
    template<>
    struct hash<Chunk::Position>
    {
        size_t operator() (const Chunk::Position& pos) const
        {
            return Hasher::hash(pos.x, pos.y);
        }
    };

    template<>
    struct hash<Chunk::Chunklet_Position>
    {
        size_t operator() (const Chunk::Chunklet_Position& pos) const
        {
            return Hasher::hash(pos.x, pos.y, pos.z);
        }
    };
}

#endif // CPOSITION_H_INCLUDED

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
    typedef sf::Vector3<int64_t> Chunklet_Position;
    typedef sf::Vector2<int64_t> Position;

    struct Chu_Blo_Pos
    {
        Chunklet_Position       chunkletPos;
        Block::Small_Position   blockPos;
    };

    /*
    struct Position
    {
        Position() = default;
        Position(int64_t x, int64_t y, int64_t z);

        int64_t  x,
                 y,
                 z;

        bool operator == (const Chunk::Position& other) const;
        const Position& operator - (const Chunk::Position& other) const;
    };
    */
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

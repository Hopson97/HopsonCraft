#ifndef BLOCK_POSITION_H_INCLUDED
#define BLOCK_POSITION_H_INCLUDED

#include <cstdint>
#include <SFML/System/Vector3.hpp>

namespace Block
{
    typedef sf::Vector3<int8_t> Small_Position;
    typedef sf::Vector3<int32_t> Column_Position;
    /*
    struct Position
    {
        Position(int8_t x, int8_t y, int8_t z);

        int8_t  x,
                y,
                z;
    };
    */
}

#endif // BLOCK_POSITION_H_INCLUDED

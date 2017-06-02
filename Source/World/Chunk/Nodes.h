#ifndef CBLOCK_H_INCLUDED
#define CBLOCK_H_INCLUDED

#include "../Block/Block_ID.h"
#include "../Block/Block_Position.h"
#include "../World_Constants.h"

/*
    These are basically things that up chunks.
    For examples, CBlocks is how chunks store blocks.
    CLight is how the chunks store light maps.
*/

namespace Block
{
    class Type;
    class Data_Holder;
}

struct CBlock
{
    CBlock();
    CBlock(Block_t      newID);
    CBlock(Block::ID    newID);
    CBlock(Block_t i, uint8_t meta);

    const Block::Data_Holder& getData() const;
    const Block::Type&        getType() const;

    template<typename T>
    CBlock& operator=(T newID)
    {
        id = static_cast<Block_t>(newID);
        return *this;
    }

    template<typename T>
    bool operator !=(T newID)
    {
        return id != static_cast<Block_t>(newID);
    }

    template<typename T>
    bool operator ==(T newID)
    {
        return id == static_cast<Block_t>(newID);
    }

    uint16_t id         : 12;   //Maximum value -> 2^12 - 1
    uint16_t metaData    : 4;   //Maximum value -> 2^4  - 1
};

struct CLight
{
    CLight();

    /*  4 bits for natural light,
        4 bits for block light
        This gives them a maximum value of 15.
        And also makes the struct just 1 byte in size!
    */
    uint8_t natural : 4;
    uint8_t block   : 4;
};

struct CPositioned_Block
{
    CPositioned_Block(const Block::Position& pos, CBlock blo)
    :   position    (pos)
    ,   block       (blo)
    {}

    const Block::Position position;
    CBlock block;
};

#endif // CBLOCK_H_INCLUDED

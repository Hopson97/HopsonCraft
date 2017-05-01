#ifndef CBLOCK_H_INCLUDED
#define CBLOCK_H_INCLUDED

#include "../Block/Block_ID.h"
#include "../Block/Block_Position.h"
#include "../World_Constants.h"

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

    uint16_t id          : 12;  //Maximum value -> 4095
    uint16_t metaData    : 4;   //Maximum value -> 15

    //meta data?
};

struct CLight
{
    CLight();

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

#ifndef CBLOCK_H_INCLUDED
#define CBLOCK_H_INCLUDED

#include "../Block/Block_ID.h"
#include "../World_Constants.h"

struct CBlock
{
    CBlock();
    CBlock(Block_t      newID);
    CBlock(Block::ID    newID);

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

    uint16_t id          : 12;
    uint16_t metaData    : 4;

    //meta data?
};

struct CLight
{
    CLight()
    :   natural    (MAX_LIGHT)
    ,   block      (MAX_LIGHT)
    { }

    uint8_t natural : 4;
    uint8_t block   : 4;
};

#endif // CBLOCK_H_INCLUDED

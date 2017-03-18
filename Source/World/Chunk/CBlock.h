#ifndef CBLOCK_H_INCLUDED
#define CBLOCK_H_INCLUDED

#include "../Block/Block_ID.h"

struct CBlock
{


    CBlock();
    CBlock(Block_t      id);
    CBlock(Block::ID    id);

    template<typename T>
    CBlock& operator=(T id)
    {
        this->id = static_cast<Block_t>(id);
        return *this;
    }

    template<typename T>
    bool operator !=(T id)
    {
        return this->id != static_cast<Block_t>(id);
    }

    template<typename T>
    bool operator ==(T id)
    {
        return this->id == static_cast<Block_t>(id);
    }

    uint16_t id          : 12;
    uint16_t metaData    : 4;

    //meta data?
};

#endif // CBLOCK_H_INCLUDED

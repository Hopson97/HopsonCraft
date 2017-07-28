#ifndef BDEFAULT_H_INCLUDED
#define BDEFAULT_H_INCLUDED

#include "BlockType.h"

class DefaultBlock : public BlockType
{
    public:
        DefaultBlock(std::string&& dataFileName);
};


#endif // BDEFAULT_H_INCLUDED

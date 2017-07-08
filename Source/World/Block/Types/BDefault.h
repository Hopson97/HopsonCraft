#ifndef BDEFAULT_H_INCLUDED
#define BDEFAULT_H_INCLUDED

#include "BlockType.h"

namespace Block
{
    class Default : public BlockType
    {
        public:
            Default(std::string&& dataFileName);
    };

    class BSand : public BlockType
    {
        public:
            BSand();
    };
}

#endif // BDEFAULT_H_INCLUDED

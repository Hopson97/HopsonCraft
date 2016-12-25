#ifndef CACTUS_H_INCLUDED
#define CACTUS_H_INCLUDED

#include "Block_Type.h"

namespace Block
{
    class Cactus : public Block_Type
    {
        public:
            Cactus();

            std::unique_ptr<Updatable_Block> getUpdatableBlock() const;
    };
}

#endif // CACTUS_H_INCLUDED

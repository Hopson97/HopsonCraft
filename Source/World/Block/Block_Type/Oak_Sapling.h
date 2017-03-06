#ifndef OAK_SAPLING_H_INCLUDED
#define OAK_SAPLING_H_INCLUDED

#include "Block_Type.h"

namespace Block
{
    class Oak_Sapling : public Block_Type
    {
        public:
            Oak_Sapling();

            std::unique_ptr<Updatable_Block> getUpdatableBlock() const override;
    };
}

#endif // OAK_SAPLING_H_INCLUDED

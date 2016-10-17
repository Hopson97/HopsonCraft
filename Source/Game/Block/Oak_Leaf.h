#ifndef OAK_LEAF_H
#define OAK_LEAF_H

#include "Block.h"

namespace Block
{
    class Oak_Leaf : public Block_Base
    {
        public:
            Oak_Leaf();

            Vector2 getTextureTop       () const override;
            Vector2 getTextureSide      () const override;
            Vector2 getTextureBottom    () const override;

            ID getID() const override;
    };
} //Namespace Block

#endif // OAK_LEAF_H

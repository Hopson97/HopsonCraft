#ifndef STONE_H
#define STONE_H

#include "Block.h"

namespace Block
{
    class Stone : public Block_Base
    {
        public:
            Stone();

            Vector2 getTextureTop       () const override;
            Vector2 getTextureSide      () const override;
            Vector2 getTextureBottom    () const override;

            bool isOpaque () const;

        private:
    };

} //Namespace Block

#endif // STONE_H

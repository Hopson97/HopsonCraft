#ifndef OAK_WOOD_H
#define OAK_WOOD_H

#include "Block.h"

namespace Block
{
    class Oak_Wood : public Block_Base
    {
        public:
            Oak_Wood();

            Vector2 getTextureTop       () const override;
            Vector2 getTextureSide      () const override;
            Vector2 getTextureBottom    () const override;

            bool isOpaque () const;

        private:
    };
} //Namespace Block

#endif // OAK_WOOD_H

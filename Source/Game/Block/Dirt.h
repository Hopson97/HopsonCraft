#ifndef DIRT_H
#define DIRT_H

#include "Block.h"

namespace Block
{
    class Dirt : public Block_Base
    {
        public:
            Dirt();

            Vector2 getTextureTop       () const override;
            Vector2 getTextureSide      () const override;
            Vector2 getTextureBottom    () const override;

            bool isOpaque () const;

        private:
    };

} //Namespace Block

#endif // DIRT_H

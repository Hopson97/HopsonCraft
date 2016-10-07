#ifndef GRASS_H
#define GRASS_H

#include "Block.h"

namespace Block
{
    class Grass : public Block_Base
    {
        public:
            Grass();

            Vector2 getTextureTop       () const override;
            Vector2 getTextureSide      () const override;
            Vector2 getTextureBottom    () const override;

        private:
    };
} //Namespace Block

#endif // GRASS_H

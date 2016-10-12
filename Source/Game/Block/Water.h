#ifndef WATER_H
#define WATER_H


#include "Block.h"

namespace Block
{
    class Water : public Block_Base
    {
        public:
            Water();

            Vector2 getTextureTop       () const override;
            Vector2 getTextureSide      () const override;
            Vector2 getTextureBottom    () const override;


    };

} //Namespace Block

#endif // WATER_H

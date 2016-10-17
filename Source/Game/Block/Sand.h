#ifndef SAND_H
#define SAND_H

#include "Block.h"

namespace Block
{
    class Sand : public Block_Base
    {
        public:
            Sand();

            Vector2 getTextureTop       () const override;
            Vector2 getTextureSide      () const override;
            Vector2 getTextureBottom    () const override;

            bool isOpaque () const;

            ID getID() const override;
    };

} //Namespace Block
#endif // SAND_H

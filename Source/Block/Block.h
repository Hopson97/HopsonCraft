#ifndef BLOCK_H
#define BLOCK_H

#include "E_Block_Type.h"

#include "OpenGL/GLM/glm_transformations.h"

namespace Block
{
    class Block_Base
    {
        public:
            Block();

            virtual bool isOpaque   () const = 0;
            virtual Id   getID      () const = 0;

            virtual Vector2 getTextureTop   () const = 0;
            virtual Vector2 getTextureSide  () const = 0;
            virtual Vector2 getTextureBottom() const = 0;
    };

} //Namespace Block

#endif // BLOCK_H

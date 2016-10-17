#ifndef BLOCK_H
#define BLOCK_H

#include "OpenGL/Glm/glm_transformations.h"
#include "E_Block_ID.h"

namespace Block
{
/*
    enum class Block_Physical_State
    {
        Solid,
        Liquid,
        Gas
    };
*/
    class Block_Base
    {
        public:
            Block_Base  ();
            virtual ~Block_Base ();

            //These get block texture location inside of the texture atlas
            virtual Vector2 getTextureTop       () const;
            virtual Vector2 getTextureSide      () const;
            virtual Vector2 getTextureBottom    () const;

            virtual bool isOpaque () const;
            //virtual Block_Physical_State getState () const;

            virtual ID getID () const;

        public:
            constexpr static int BLOCK_ATLAS_SIZE   = 4096;
            constexpr static int TEXTURE_SIZE       = 128;
    };
} //Namespace Block

typedef Block::Block_Base Block_t;

#endif // BLOCK_H

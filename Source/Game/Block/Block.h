#ifndef BLOCK_H
#define BLOCK_H

#include "OpenGL/Glm/glm_transformations.h"

namespace Block
{

    enum class ID
    {
        Air,
        Grass,
        Dirt,
        Stone,
        Sand,
        Water,
        Oak_Wood,
        Oak_Leaf,
        NUM_BLOCK_TYPES
    };

    class Block_Base
    {
        public:
            Block_Base  ( ID id );
            virtual ~Block_Base ();

            //These get block texture location inside of the texture atlas
            virtual Vector2 getTextureTop       () const;
            virtual Vector2 getTextureSide      () const;
            virtual Vector2 getTextureBottom    () const;

            virtual bool isOpaque () const;

            ID getID () const;

        private:
            ID m_id;

        public:
            constexpr static int BLOCK_ATLAS_SIZE   = 4096;
            constexpr static int TEXTURE_SIZE       = 128;
    };
} //Namespace Block

typedef Block::Block_Base Block_t;

#endif // BLOCK_H

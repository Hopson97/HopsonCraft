#ifndef BLOCK_H
#define BLOCK_H

#include "OpenGL/Glm/glm_transformations.h"
#include "E_Block_ID.h"

#include <string>

namespace Block
{
    class Block_Base
    {
        public:
            Block_Base  (const std::string& name = "Air");
            virtual ~Block_Base ();

            ID getID () const;

            //These get block texture location inside of the texture atlas
            const Vector2& getTextureTop    () const;
            const Vector2& getTextureSide   () const;
            const Vector2& getTextureBottom () const;

            bool isOpaque () const;

        private:
            ID m_id;

            Vector2 m_topTexture;
            Vector2 m_sideTexture;
            Vector2 m_bottomTexture;

            bool m_isOpaque;

    };
} //Namespace Block

typedef Block::Block_Base Block_t;

#endif // BLOCK_H

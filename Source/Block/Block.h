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

            const std::string& getName() const;

            ID getID () const;

            //These get block texture location inside of the texture atlas
            const Vector2& getTextureTop    () const;
            const Vector2& getTextureSide   () const;
            const Vector2& getTextureBottom () const;

            bool isOpaque () const;

            int getBlastRestistance() const;

        private:
            void loadFromFile();

            std::string m_name;

            ID m_id;

            Vector2 m_topTexture;
            Vector2 m_sideTexture;
            Vector2 m_bottomTexture;

            bool m_isOpaque;

            int m_blastRestistance; //The "power" from a blast must be greater than this

    };
} //Namespace Block

typedef Block::Block_Base Block_t;

#endif // BLOCK_H

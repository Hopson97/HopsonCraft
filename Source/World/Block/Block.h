#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>

#include "../../OpenGL/GL_Maths.h"
#include "E_Block_ID.h"
#include "E_Block_Physical_State.h"
#include "E_Block_Type.h"

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

            Physical_State  getPhysicalState()  const;
            Mesh_Type       getMeshType()       const;

            bool canBePlacedOn (const Block_Base& block) const;

        private:
            void loadFromFile();

            std::string m_name;

            ID m_id;

            Vector2 m_topTexture;
            Vector2 m_sideTexture;
            Vector2 m_bottomTexture;

            bool m_isOpaque = false;

            int m_blastRestistance = 0; //The "power" from a blast must be greater than this

            Physical_State m_state;
            Mesh_Type m_meshType;

            std::vector<ID> m_blocksCanBePlacedOn;
    };
} //Namespace Block

typedef Block::Block_Base Block_t;

#endif // BLOCK_H

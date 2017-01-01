#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>

#include "../../OpenGL/GL_Maths.h"
#include "Block_Enums.h"

/*
    General Block Data Stuff
*/

namespace Block
{
    class Block_Data
    {
        public:
            Block_Data  (const std::string& name);

            const std::string& getName() const;

            ID getID () const;

            //These get block texture location inside of the texture atlas
            const Vector2& getTextureTop    () const;
            const Vector2& getTextureSide   () const;
            const Vector2& getTextureBottom () const;



            int getBlastRestistance() const;

            Physical_State  getPhysicalState()  const;
            Mesh_Type       getMeshType()       const;

            bool canBePlacedOn  (const Block_Data& block) const;
            bool isUpdatable    () const;
            bool isOpaque       () const;
            bool isFullBlock    () const;

            float getHeight     () const;

            int getLightChange  () const;
            int getLightEmission() const;

        private:
            void loadFromFile();

            std::string m_name;

            ID m_id;

            Vector2 m_topTexture;
            Vector2 m_sideTexture;
            Vector2 m_bottomTexture;

            bool m_isOpaque     = false;
            bool m_isUpdatable  = false;
            bool m_isFullBlock  = true;

            float m_height      = 1.0f;

            int m_blastRestistance = 0; //The "power" from a blast must be greater than this

            Physical_State m_state;
            Mesh_Type m_meshType;

            std::vector<ID> m_blocksCanBePlacedOn;

            int m_lightChange   = -1;
            int m_lightEmission = 0;
    };
} //Namespace Block

#endif // BLOCK_H

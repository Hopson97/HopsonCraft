#ifndef BLOCK_DATA_H_INCLUDED
#define BLOCK_DATA_H_INCLUDED

#include <string>
#include "Block_ID.h"
#include "../../Glm_Common.h"

namespace Block
{
    class Data
    {
        public:
           Data(const std::string& fileName);

           const Vector2& getTopTex() const;
           const Vector2& getSideTex() const;
           const Vector2& getBottomTex() const;

        private:
            ID m_blockID;

            std::string m_name;

            bool m_isOpaque;

            Vector2 m_topTextureCoords;
            Vector2 m_sideTextureCoords;
            Vector2 m_bottomTextureCoords;
    };
}

#endif // BLOCK_DATA_H_INCLUDED

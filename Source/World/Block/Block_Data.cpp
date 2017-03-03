#include "Block_Data.h"

#include <fstream>


namespace Block
{
    Data::Data(const std::string& fileName)
    {
        std::ifstream inFile;

        inFile.open("Data/Blocks/" + fileName + ".block");

        std::string title;

        while (std::getline(inFile, title))
        {
            if (title == "") continue;
            else if (title == "Name")
            {
                inFile >> m_name;
            }
            else if (title == "ID")
            {
                int tempID;
                inFile >> tempID;
                m_blockID = static_cast<ID>(tempID);
            }
            else if (title == "Opaque")
            {
                inFile >> m_isOpaque;
            }
            else if (title == "TextureTop")
            {
                inFile >> m_topTextureCoords.x >> m_topTextureCoords.y;
            }
            else if (title == "TextureSide")
            {
                inFile >> m_sideTextureCoords.x >> m_sideTextureCoords.y;
            }
            else if (title == "TextureBottom")
            {
                inFile >> m_bottomTextureCoords.x >> m_bottomTextureCoords.y;
            }
        }
    }

    const Vector2& Data::getTopTex() const
    {
        return m_topTextureCoords;
    }

    const Vector2& Data::getSideTex() const
    {
        return m_sideTextureCoords;
    }

    const Vector2& Data::getBottomTex() const
    {
        return m_bottomTextureCoords;
    }

}

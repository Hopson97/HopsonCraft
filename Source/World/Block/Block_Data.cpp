#include "Block_Data.h"

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
                inFile >> m_holder.name;
            }
            else if (title == "ID")
            {
                loadEnum(inFile, m_holder.blockID);
            }
            else if (title == "Opaque")
            {
                inFile >> m_holder.isOpaque;
            }
            else if (title == "Obstacle")
            {
                inFile >> m_holder.isObstacle;
            }
            else if (title == "Mesh")
            {
                loadEnum(inFile, m_holder.meshType);
            }
            else if (title == "TextureTop")
            {
                inFile >> m_holder.topTextureCoords.x >> m_holder.topTextureCoords.y;
            }
            else if (title == "TextureSide")
            {
                inFile >> m_holder.sideTextureCoords.x >> m_holder.sideTextureCoords.y;
            }
            else if (title == "TextureBottom")
            {
                inFile >> m_holder.bottomTextureCoords.x >> m_holder.bottomTextureCoords.y;
            }
        }
    }
}

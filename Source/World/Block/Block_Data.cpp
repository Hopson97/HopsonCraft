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
                inFile >> m_holder.name;
            }
            else if (title == "ID")
            {
                int tempID;
                inFile >> tempID;
                m_holder.blockID = static_cast<ID>(tempID);
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
                int mesh;
                inFile >> mesh;
                m_holder.meshType = static_cast<Mesh_Type>(mesh);
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

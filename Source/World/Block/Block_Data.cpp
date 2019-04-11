#include "Block_Data.h"

#include <iostream>
#include <fstream>

#include "../../Util/File_Util.h"

#include "../../Util/STD_Util.h"

namespace Block
{
    Data::Data(std::string&& fileName)
    :   m_fileName  (std::move(fileName))
    {
        std::string fullName = "Data/Blocks/" + m_fileName + ".block";
        Loader::load(fullName);
    }

    bool Data::parseLine(const std::string& line, std::ifstream& inFile)
    {
        if(areStringsSame(line, "Name"))
        {
            std::getline(inFile, m_holder.name);
        }
        else if (areStringsSame(line, "ID"))
        {
            loadEnum(inFile, m_holder.blockID);
        }
        else if (areStringsSame(line, "Opaque"))
        {
            inFile >> m_holder.isOpaque;
        }
        else if (areStringsSame(line, "Obstacle"))
        {
            inFile >> m_holder.isObstacle;
        }
        else if (areStringsSame(line, "Update"))
        {
            inFile >> m_holder.canUpdate;
        }
        else if (areStringsSame(line, "Mesht"))
        {
            loadEnum(inFile, m_holder.meshType);
        }
        else if (areStringsSame(line, "Style"))
        {
            loadEnum(inFile, m_holder.meshStyle);
        }
        else if (areStringsSame(line, "State"))
        {
            loadEnum(inFile, m_holder.state);
        }
        else if (areStringsSame(line, "Texture Top"))
        {
            inFile  >> m_holder.topTextureCoords.x
                    >> m_holder.topTextureCoords.y;
        }
        else if (areStringsSame(line, "Texture Side"))
        {
            inFile  >> m_holder.sideTextureCoords.x
                    >> m_holder.sideTextureCoords.y;
        }
        else if (areStringsSame(line, "Texture Bottom"))
        {
            inFile  >> m_holder.bottomTextureCoords.x
                    >> m_holder.bottomTextureCoords.y;
        }
        else
        {
            return false;
        }
        return true;
    }
}
















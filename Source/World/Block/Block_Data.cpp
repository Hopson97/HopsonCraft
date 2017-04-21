#include "Block_Data.h"

#include "../../Util/json.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace
{
    std::string getFileContents(const std::string& filePath)
    {
        std::ifstream inFile(filePath);
        std::stringstream stream;

        stream << inFile.rdbuf();   //Gets the file contents into a string stream
        return stream.str();        //Return the string from the string stream
    }
}

namespace Block
{
    Data::Data(const std::string& fileName)
    {
        auto source = getFileContents("Data/Blocks/" + fileName + ".json");
        nlohmann::json jsonFile = nlohmann::json::parse(source.c_str());

        m_holder.name       = jsonFile["Name"]      .get<std::string>();
        m_holder.isOpaque   = jsonFile["Opaque"]    .get<bool>();
        m_holder.isObstacle = jsonFile["Obstacle"]  .get<bool>();

        m_holder.blockID    = (Block::ID) jsonFile["ID"]    .get<int32_t>();
        m_holder.meshType   = (Mesh_Type) jsonFile["Mesh"]  .get<int32_t>();

        auto getTexCoords = [&](const std::string& loc, Vector2& vect)
        {
            auto uv = jsonFile["Texture " + loc].get<std::vector<float>>();
            vect.x = uv[0];
            vect.y = uv[1];
        };

        getTexCoords("Top",     m_holder.topTextureCoords);
        getTexCoords("Side",    m_holder.sideTextureCoords);
        getTexCoords("Bottom",  m_holder.bottomTextureCoords);
    }
}

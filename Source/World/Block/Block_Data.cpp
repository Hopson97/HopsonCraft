#include "Block_Data.h"

#include "../../Util/json.hpp"

#include <iostream>

#include "../../Util/File_Util.h"

namespace Block
{
    Data::Data(const std::string& fileName)
    {
        auto source = getFileContents("Data/Blocks/" + fileName + ".json");
        nlohmann::json jsonFile = nlohmann::json::parse(source.c_str());

        m_holder.name       = jsonFile["Name"]      .get<std::string>();
        m_holder.isOpaque   = jsonFile["Opaque"]    .get<bool>();
        m_holder.isObstacle = jsonFile["Obstacle"]  .get<bool>();
        m_holder.canUpdate  = jsonFile["Updates"]   .get<bool>();

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

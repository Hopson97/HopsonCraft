#include "Block_Data.h"

#include <fstream>
#include <stdexcept>

//to do: load blocks from files

namespace Block
{
    Block_Data::Block_Data(const std::string& name)
    :   m_name (name)
    {
        loadFromFile();
    }

    const std::string& Block_Data::getName() const
    {
        return m_name;
    }

    ID Block_Data::getID () const
    {
        return m_id;
    }

    const Vector2& Block_Data::getTextureTop () const
    {
        return m_topTexture;
    }

    const Vector2& Block_Data::getTextureSide () const
    {
        return m_sideTexture;
    }

    const Vector2& Block_Data ::getTextureBottom () const
    {
        return m_bottomTexture;
    }

    bool Block_Data::isOpaque () const
    {
        return m_isOpaque;
    }

    int Block_Data::getBlastRestistance() const
    {
        return m_blastRestistance;
    }

    Physical_State Block_Data::getPhysicalState() const
    {
        return m_state;
    }

    Mesh_Type Block_Data::getMeshType() const
    {
        return m_meshType;
    }

    bool Block_Data::canBePlacedOn (const Block::Block_Data& block) const
    {
        if (m_blocksCanBePlacedOn.empty()) return true;
        else
        {
            for (auto& id : m_blocksCanBePlacedOn)
            {
                if (block.getID() == id) return true;
            }
        }
        return false;
    }

    bool Block_Data::isUpdatable() const
    {
        return m_isUpdatable;
    }

    /*
        Every block has its constant data loaded from a file.
    */
    void Block_Data::loadFromFile()
    {
        std::ifstream inFile ("Data/Blocks/" + m_name + ".block");
        if (!inFile.is_open())
        {
            throw std::runtime_error ("Unable to load block:" + m_name);
        }


        std::string line;
        while (std::getline(inFile, line))
        {
            if (line == "id")
            {
                int id;
                inFile >> id;
                m_id = static_cast<ID>(id);
            }
            else if (line == "txrtop") //Coords of the texture top from the texture atlas
            {
                inFile >> m_topTexture.x >> m_topTexture.y;
            }
            else if (line == "txrside") //Coords of the texture side from the texture atlas
            {
                inFile >> m_sideTexture.x >> m_sideTexture.y;
            }
            else if (line == "txrbottom") //Coords of the texture bottom from the texture atlas
            {
                inFile >> m_bottomTexture.x >> m_bottomTexture.y;
            }
            else if (line == "opaque") //Is the block opaque or nah
            {
                inFile >> m_isOpaque;
            }
            else if (line == "blastres")    //"resistance" from "explositions"
            {
                inFile >> m_blastRestistance;
            }
            else if (line == "physstate")   //The physical state
            {
                int state;
                inFile >> state;
                m_state = static_cast<Physical_State>(state);
            }
            else if (line == "meshtype")    //Mesh type, cube or X shaped
            {
                int type;
                inFile >> type;
                m_meshType = static_cast<Mesh_Type>(type);
            }
            else if(line == "placeon")  //Some blocks can only be placed on specific blocks, so this is where it gets listed
            {
                std::getline(inFile, line);
                while (line != "end")
                {
                    auto block = std::stoi(line);
                    m_blocksCanBePlacedOn.push_back(static_cast<ID>(block));
                    std::getline(inFile, line);
                }
            }
            else if (line == "upt")
            {
                inFile >> m_isUpdatable;
            }
            else if (line == "") continue;
            else
            {
                throw std::runtime_error ("Unrecognised word in " + m_name + ".block -> " + line + "!");
            }
        }
    }


} //Namespace Block

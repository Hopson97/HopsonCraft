#include "Block.h"

#include <fstream>
#include <stdexcept>

//to do: load blocks from files

namespace Block
{
    Block_Base::Block_Base(const std::string& name)
    :   m_name (name)
    {
        loadFromFile();
    }

    const std::string& Block_Base::getName() const
    {
        return m_name;
    }

    Block_Base::~Block_Base ()
    { }

    ID Block_Base::getID () const
    {
        return m_id;
    }

    const Vector2& Block_Base::getTextureTop () const
    {
        return m_topTexture;
    }

    const Vector2& Block_Base::getTextureSide () const
    {
        return m_sideTexture;
    }

    const Vector2& Block_Base ::getTextureBottom () const
    {
        return m_bottomTexture;
    }

    bool Block_Base::isOpaque () const
    {
        return m_isOpaque;
    }

    int Block_Base::getBlastRestistance() const
    {
        return m_blastRestistance;
    }

    Physical_State Block_Base::getPhysicalState() const
    {
        return m_state;
    }

    Mesh_Type Block_Base::getMeshType() const
    {
        return m_meshType;
    }

    bool Block_Base::canBePlacedOn (const Block_t& block) const
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

    void Block_Base::loadFromFile()
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
            else if (line == "txrtop")
            {
                inFile >> m_topTexture.x >> m_topTexture.y;
            }
            else if (line == "txrside")
            {
                inFile >> m_sideTexture.x >> m_sideTexture.y;
            }
            else if (line == "txrbottom")
            {
                inFile >> m_bottomTexture.x >> m_bottomTexture.y;
            }
            else if (line == "opaque")
            {
                inFile >> m_isOpaque;
            }
            else if (line == "blastres")
            {
                inFile >> m_blastRestistance;
            }
            else if (line == "physstate")
            {
                int state;
                inFile >> state;
                m_state = static_cast<Physical_State>(state);
            }
            else if (line == "meshtype")
            {
                int type;
                inFile >> type;
                m_meshType = static_cast<Mesh_Type>(type);
            }
            else if(line == "placeon")
            {
                std::getline(inFile, line);
                while (line != "end")
                {
                    auto block = std::stoi(line);
                    m_blocksCanBePlacedOn.push_back(static_cast<ID>(block));
                    std::getline(inFile, line);
                }
            }
            else if (line == "") continue;
            else
            {
                throw std::runtime_error ("Unrecognised word in " + m_name + ".block -> " + line + "!");
            }
        }
    }


} //Namespace Block

#include "block.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

//to do: load blocks from files

namespace Block
{
    Block_Base :: Block_Base(const std::string& name)
    {
        std::ifstream inFile ("Data/Blocks/" + name + ".block");
        if (!inFile.is_open())
        {
            throw std::runtime_error ("Unable to load block:" + name);
        }


        if ( name == "Grass" ) std::cout << "GRASSY1" << std::endl;
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
                if ( name == "Grass" ) std::cout << "GRASSY2" << std::endl;
                std::cout << "side" << std::endl;
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
        }
    }

    Block_Base :: ~Block_Base ()
    { }

    ID Block_Base :: getID () const
    {
        return m_id;
    }

    const Vector2& Block_Base :: getTextureTop () const
    {
        return m_topTexture;
    }

    const Vector2& Block_Base :: getTextureSide () const
    {
        return m_sideTexture;
    }

    const Vector2& Block_Base :: getTextureBottom () const
    {
        return m_bottomTexture;
    }

    bool Block_Base :: isOpaque () const
    {
        return m_isOpaque;
    }
} //Namespace Block

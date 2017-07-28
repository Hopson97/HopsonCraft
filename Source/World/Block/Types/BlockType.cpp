#include "BlockType.h"

BlockType::BlockType(std::string&& fileName)
:   m_data (std::move(fileName))
{

}

const BlockData& BlockType::getData() const
{
    return m_data;
}

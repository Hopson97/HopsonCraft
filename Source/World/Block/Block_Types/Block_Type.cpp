#include "Block_Type.h"

namespace Block
{
    Type::Type(std::string&& fileName)
    :   m_data (std::move(fileName))
    {

    }

    const Data& Type::getData() const
    {
        return m_data;
    }

}

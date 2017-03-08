#include "Block_Type.h"

namespace Block
{
    Type::Type(const std::string& fileName)
    :   m_data (fileName)
    {

    }

    const Data& Type::getData() const
    {
        return m_data;
    }

}

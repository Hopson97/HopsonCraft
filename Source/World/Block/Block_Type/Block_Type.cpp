#include "Block_Type.h"

namespace Block
{
    Block_Type::Block_Type(const std::string& name)
    :   m_data(name)
    { }

    const Block_Data& Block_Type::getData() const
    {
        return m_data;
    }
}

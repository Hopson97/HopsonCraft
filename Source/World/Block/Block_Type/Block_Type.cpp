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

    std::vector<Temp_Item_ID> Block_Type::getLoot() const
    {
        return {Empty()};
    }

    std::unique_ptr<Updatable_Block> Block_Type::getUpdatableBlock() const
    {
        return nullptr;
    }

    Interaction_Type Block_Type::interact(Chunk& chunk, const Block_Location& location, Temp_Item_ID id) const
    {
        return Interaction_Type::None;
    }
}

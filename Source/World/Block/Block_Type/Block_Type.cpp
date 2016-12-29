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

    bool Block_Type::tick(const Block_Location& location, Chunk* chunk) const
    {
        return false;
    }


    Interaction_Type Block_Type::interact(World& world, Chunk& chunk, const Vector3& location, Temp_Item_ID id) const
    {
        return Interaction_Type::None;
    }

    void Block_Type::breakBlock(World& world, Chunk& chunk, const Vector3& location, Break_Type breakType) const
    { }

}

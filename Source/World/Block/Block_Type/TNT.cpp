#include "TNT.h"

#include "../../World.h"

namespace Block
{
    TNT::TNT()
    :   Block_Type("TNT")
    { }

    Interaction_Type TNT::interact(World& world, Chunk& chunk, const Vector3& location, Temp_Item_ID id) const
    {
        world.makeExplosion(location, 10);
        return Interaction_Type::None;
    }

}

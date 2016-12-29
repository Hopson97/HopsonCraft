#ifndef TNT_H_INCLUDED
#define TNT_H_INCLUDED

#include "Block_Type.h"

namespace Block
{
    class  TNT : public Block_Type
    {
        public:
            TNT();

            Interaction_Type interact(World& world, Chunk& chunk, const Vector3& location, Temp_Item_ID id) const;
    };
}

#endif // TNT_H_INCLUDED

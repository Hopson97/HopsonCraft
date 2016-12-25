#ifndef GRASS_H_INCLUDED
#define GRASS_H_INCLUDED

#include "Block_Type.h"

namespace Block
{
    class Grass : public Block_Type
    {
        public:
            Grass();
            Interaction_Type interact(Chunk& chunk, const Block_Location& location, Temp_Item_ID id) const;
    };
}

#endif // GRASS_H_INCLUDED

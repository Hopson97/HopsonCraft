#include "Oak_Sapling.h"

#include <iostream>

#include "../Updateable/U_Oak_Sapling.h"

namespace Block
{
    Oak_Sapling::Oak_Sapling()
    :   Block_Type ("Oak_Sapling")
    { }

    std::unique_ptr<Updatable_Block> Oak_Sapling::getUpdatableBlock() const
    {
        return std::make_unique<U_Oak_Sapling>();
    }
}

#include "Cactus.h"

#include "../Updateable/U_Cactus.h"

namespace Block
{
    Cactus::Cactus()
    :   Block_Type ("Cactus")
    { }

    std::unique_ptr<Updatable_Block> Cactus::getUpdatableBlock() const
    {
        //return std::make_unique<U_Cactus>();
    }
}

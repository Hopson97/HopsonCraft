#ifndef GENERAL_MATHS_H_INCLUDED
#define GENERAL_MATHS_H_INCLUDED

#include "../Glm_Common.h"
#include "../World/Chunk/CPosition.h"
#include "../World/Block/Block_Position.h"

namespace Maths
{
    template<typename T, typename R>
    bool inRange(T var, R low, R high)
    {
        return  var <= high &&
                var >= low;
    }

    template<typename T, typename L>
    bool lessThan(T var, L val)
    {
        return var < val;
    }

}

#endif // GENERAL_MATHS_H_INCLUDED

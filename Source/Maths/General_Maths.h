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

    float bilinearInterpolate(float q11, float q12, float q21, float q22,
                              float x1,  float x2,
                              float y1,  float y2,
                              float x,   float y);

}

#endif // GENERAL_MATHS_H_INCLUDED

#ifndef GENERAL_MATHS_H_INCLUDED
#define GENERAL_MATHS_H_INCLUDED

#include "../Glm_Common.h"
#include "../World/Chunk/Position.h"
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

    float bilinearInterpolate(float bottomLeft, float topLeft, float bottomRight, float topRight,
                              float xMin,       float xMax,
                              float yMin,       float yMax,
                              float xToCalc,    float yToCalc);

}

#endif // GENERAL_MATHS_H_INCLUDED

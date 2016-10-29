#include "Maths/General_Maths.h"

#include <cmath>

namespace Maths
{
    double getDistance (const Vector3& p1, const Vector3& p2)
    {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        double dz = p1.z - p2.z;

        return std::abs (std::sqrt(dx * dx + dy * dy + dz * dz));
    }
}//namespace maths

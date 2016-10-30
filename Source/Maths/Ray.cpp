#include "Ray.h"

#include <cmath>

namespace Maths
{
    Ray::Ray(float yaw, float pitch, const Vector3& origin)
    :   m_yaw       (glm::radians(yaw))
    ,   m_pitch     (glm::radians(pitch))
    ,   m_origin    (origin)
    ,   m_endPoint  (origin)
    {}

    void Ray::step(float scaler)
    {
        m_endPoint.x -= cos (m_yaw)   * scaler;
        m_endPoint.z -= sin (m_yaw)   * scaler;
        m_endPoint.y -= tan (m_pitch) * scaler;
    }

    const Vector3& Ray::getEndPoint() const
    {
        return m_endPoint;
    }
}

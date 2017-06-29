#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "../Maths/GLM.h"

class Ray
{
    public:
        Ray(float yaw, float pitch, const Vector3& origin) noexcept;

        void step (float scaler) noexcept;
        const Vector3& getEndPoint() const noexcept;

        float getLength() noexcept;

    private:
        float m_yaw;
        float m_pitch;
        Vector3 m_startPoint;
        Vector3 m_endPoint;
};

#endif // RAY_H_INCLUDED

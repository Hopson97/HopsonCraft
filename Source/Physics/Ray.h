#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "../Glm_Common.h"

class Ray
{
    public:
        Ray(float yaw, float pitch, const Vector3& origin);

        void step (float scaler);
        const Vector3& getEndPoint() const;

        float getLength();

    private:
        float m_yaw;
        float m_pitch;
        Vector3 m_startPoint;
        Vector3 m_endPoint;
};

#endif // RAY_H_INCLUDED

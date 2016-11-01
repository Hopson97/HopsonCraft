#ifndef RAY_H
#define RAY_H

#include "OpenGL/GLM/glm_transformations.h"

namespace Maths
{
    class Ray
    {
        public:
            Ray(float yaw, float pitch, const Vector3& origin);

            void step (float scaler);
            void set  (float scaler);

            const Vector3& getEndPoint() const;

        private:
            float m_yaw;
            float m_pitch;
            Vector3 m_origin;
            Vector3 m_endPoint;
    };
}
#endif // RAY_H

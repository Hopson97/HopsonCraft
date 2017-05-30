#ifndef GLM_COMMON_H_INCLUDED
#define GLM_COMMON_H_INCLUDED

#include "Util/Hasher.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;

typedef glm::mat4 Matrix4;

namespace std
{
    template<>
    struct hash<Vector3>
    {
        size_t operator() (const Vector3& vect) const
        {
            return Hasher::hash(vect.x, vect.y, vect.z);
        }
    };
}

#endif // GLM_COMMON_H_INCLUDED

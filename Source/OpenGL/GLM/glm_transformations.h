#ifndef GLM_TRANSFORMATIONS_H_INCLUDED
#define GLM_TRANSFORMATIONS_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <functional>

#include "../../Util/Hasher.h"

typedef glm::mat4 Matrix4;
typedef glm::vec4 Vector4;
typedef glm::vec3 Vector3;
typedef glm::vec2 Vector2;

namespace std
{
    template<>
    struct hash<Vector2>
    {
        size_t operator() (Vector2 const& v) const
        {
            return Hasher::hash(v.x, v.y);
        }
    };
}

#endif // GLM_TRANSFORMATIONS_H_INCLUDED

#ifndef ENTITY_H
#define ENTITY_H

#include "../OpenGL/GLM/glm_transformations.h"

struct Entity
{
    Entity() = default;
    Entity(const Vector3& rotation,
           const Vector3& position,
           const Vector3& scale = {1, 1, 1});

    Vector3 rotation;
    Vector3 position;
    Vector3 scale       = {1, 1, 1};
};

#endif // ENTITY_H

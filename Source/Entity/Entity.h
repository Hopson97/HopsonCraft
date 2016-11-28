#ifndef ENTITY_H
#define ENTITY_H

#include "../OpenGL/GL_Maths.h"

struct Entity
{
    Entity() = default;
    Entity(const Vector3& rotation,
           const Vector3& position,
           const Vector3& scale = {1, 1, 1});

    Vector3 rotation;
    Vector3 position;
    Vector3 scale       = {1, 1, 1};

    virtual ~Entity() = default;
};

#endif // ENTITY_H

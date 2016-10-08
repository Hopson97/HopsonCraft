#ifndef VECTOR_H
#define VECTOR_H

#include <functional>
#include <cmath>

#include "OpenGL/Glm/glm_transformations.h"

struct Vector2i
{
    Vector2i ( int x, int z );

    int x;
    int z;

    bool operator == ( const Vector2i& other ) const;
};

namespace std
{
    template<> struct hash<Vector2i>
    {

        size_t operator() ( Vector2i const& v ) const
        {
            size_t h1 = std::hash<double>()(v.x);
            size_t h2 = std::hash<double>()(v.z);
            return (h1 ^ (h2 << 1));
        }
    };
}

#endif // VECTOR_H

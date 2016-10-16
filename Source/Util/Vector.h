#ifndef VECTOR_H
#define VECTOR_H

#include <functional>
#include <cmath>

#include "OpenGL/Glm/glm_transformations.h"

struct Vector2i
{
    Vector2i ( int x, int z );

    int x = 0;
    int z = 0;

    bool operator == ( const Vector2i& other ) const;

    bool operator !=  ( const Vector2i& other ) const;
};

namespace std
{
    template<>
    struct hash<Vector2i>
    {
        template <typename T>
        T hashInt( T key ) const
        {
            key = ~key + (key << 15);
            key = key ^ (key >> 12);
            key = key + (key << 2);
            key = key ^ (key >> 4);
            key = key * 2057;
            key = std::hash<double>{}(key ^ (key >> 16));
            return key;
        }

        size_t operator() ( Vector2i const& v ) const
        {
            size_t h1 = std::hash<double>()( hashInt ( v.x >> v.z ) );
            size_t h2 = std::hash<double>()( hashInt ( v.x << v.z ) );
            return (h1 ^ (h2 << 1));
        }
    };
}

#endif // VECTOR_H

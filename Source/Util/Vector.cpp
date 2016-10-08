#include "vector.h"

Vector2i :: Vector2i ( int x, int z )
: x     ( x )
, z     ( z ){}

bool Vector2i :: operator == ( const Vector2i& other ) const
{
    return (x == other.x) && (z == other.z);
}

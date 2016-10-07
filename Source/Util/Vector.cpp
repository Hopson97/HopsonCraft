#include "vector.h"

int Vector2i :: id = 0;

Vector2i :: Vector2i ( int x, int y )
: x     ( x )
, y     ( y )
, m_id  ( ++id ) {}

int x;
int y;

bool Vector2i :: operator < ( const Vector2i& other ) const
{
    return m_id < other.m_id;
}

bool Vector2i :: operator > ( const Vector2i& other ) const
{
    return m_id > other.m_id;
}

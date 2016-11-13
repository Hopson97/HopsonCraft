#include "Block_Location.h"

Block_Location::Block_Location (char x, int y, char z)
:   x   (x)
,   y   (y)
,   z   (z)
{}

bool Block_Location::operator== (const Block_Location& other) const
{
    return (x == other.x) && (y == other.y) && (z == other.z);
}


bool Block_Location::operator!= (const Block_Location& other) const
{
    return !((x == other.x) && (y == other.y) && (z == other.z));
}

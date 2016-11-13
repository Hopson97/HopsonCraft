#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "../Block/Block_Location.h"

#include <functional>

class Chunk;


namespace Structure
{
    void createOak(Chunk& chunk, const Block_Location& location);

    void createCactus(Chunk& chunk, const Block_Location& location);
}

#endif // STRUCTURE_H

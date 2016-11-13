#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "../Block/Block_Location.h"

#include <functional>

class Chunk;


typedef std::function<void(Chunk& chunk, const Block_Location& location)> Structure_Function;

namespace Structure
{
    extern Structure_Function makeOak;
    extern Structure_Function makeCactus;
}





#endif // STRUCTURE_H

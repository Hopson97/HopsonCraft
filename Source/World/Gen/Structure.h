#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "../Block/Block_Location.h"

#include <functional>

class Chunk;


typedef std::function<void(Chunk& chunk, const Block_Location& location, bool overwrite)> Structure_Function;

namespace Structure
{
    void createOak      (Chunk& chunk, const Block_Location& location, bool overwriteBlocks = false);
    void createCactus   (Chunk& chunk, const Block_Location& location, bool overwriteBlocks = false);
    void createSpruce   (Chunk& chunk, const Block_Location& location, bool overwriteBlocks = false);

    extern Structure_Function   makeOak;
    extern Structure_Function   makeCactus;
    extern Structure_Function   makeSpruce;
}

#endif // STRUCTURE_H

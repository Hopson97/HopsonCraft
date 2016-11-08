#ifndef TREE_H
#define TREE_H

class Chunk;
class Block_Location;

namespace Tree
{
    void makeOakTree    (Chunk& chunk, const Block_Location& location);
    void makeCactus     (Chunk& chunk, const Block_Location& location);
}

#endif // TREE_H

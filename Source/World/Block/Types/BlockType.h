#ifndef BLOCK_TYPE_H
#define BLOCK_TYPE_H

#include <string>

#include "../BlockData.h"
#include "../BlockPosition.h"

class World;
class CBlock;

class BlockType
{
    public:
        const BlockData& getData() const;

        virtual void tick   (World& world, CBlock& block, const BlockPosition& position) const{}
        virtual void trigger(World& world, CBlock& block, const BlockPosition& position) const{}

    protected:
        BlockType(std::string&& fileName);

    private:
        BlockData m_data;
};

#endif // BLOCK_TYPE_H

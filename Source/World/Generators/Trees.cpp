#include "Trees.h"

#include "../Chunk/CNodes.h"
#include "../IBlock_Accessible.h"

class Tree_Helper
{
    struct Defer_Block
    {
        Defer_Block(int x, int y, int z, CBlock b)
        :   pos     (x, y, z)
        ,   block   (b)
        { }

        Block::Position pos;
        CBlock block;
    };

    public:
        Tree_Helper(CBlock leaf, CBlock wood)
        :   m_leafBlock (leaf)
        ,   m_woodBlock (wood)
        { }

        void addLeaf(int x, int y, int z)
        {
            m_deferBlocks.emplace_back(x, y, z, m_leafBlock);
        }

        void addAir (int x, int y, int z)
        {
            m_deferBlocks.emplace_back(x, y, z, Block::ID::Air);
        }

        void addWood(int x, int y, int z)
        {
            m_deferBlocks.emplace_back(x, y, z, m_woodBlock);
        }

        void build(IBlock_Accessible& access)
        {
            for (auto& block : m_deferBlocks)
            {
                int x = block.pos.x;
                int y = block.pos.y;
                int z = block.pos.z;
                access.setBlock(x, y, z, block.block);
            }
        }

    private:
        std::vector<Defer_Block> m_deferBlocks;

        CBlock m_leafBlock;
        CBlock m_woodBlock;

};


void makeOakTree(IBlock_Accessible& access,
                 const Block::Position& pos,
                 Random::Generator<std::mt19937>& random)
{
    Tree_Helper tree(Block::ID::Oak_Leaf,
                     Block::ID::Oak_Wood);

    int height      = Random::intInRange(5, 8);
    int crownSize   = 2;

    for (int32_t zLeaf = -crownSize; zLeaf <= crownSize; zLeaf++)
    for (int32_t xLeaf = -crownSize; xLeaf <= crownSize; xLeaf++)
    {
        tree.addLeaf(pos.x + xLeaf, pos.y + height - 1,   pos.z + zLeaf);
        tree.addLeaf(pos.x + xLeaf, pos.y + height,       pos.z + zLeaf);
    }

    for (int32_t zLeaf = -crownSize + 1; zLeaf <= crownSize - 1; zLeaf++)
    {
        tree.addLeaf(pos.x, pos.y + height + 1, pos.z + zLeaf);
    }

    for (int32_t xLeaf = -crownSize + 1; xLeaf <= crownSize - 1; xLeaf++)
    {
        tree.addLeaf(pos.x + xLeaf, pos.y + height + 1, pos.z);
    }

    int h = pos.y + height;
    tree.addAir(pos.x + crownSize, h, pos.z + crownSize);
    tree.addAir(pos.x - crownSize, h, pos.z + crownSize);
    tree.addAir(pos.x + crownSize, h, pos.z - crownSize);
    tree.addAir(pos.x - crownSize, h, pos.z - crownSize);
    tree.addLeaf(pos.x, pos.y + height + 2, pos.z);

    for (int y = 1; y < height; y++)
    {
        tree.addWood(pos.x, pos.y + y, pos.z);
    }

    tree.build(access);
}

void makePalmTree(IBlock_Accessible& access,
                  const Block::Position& pos,
                  Random::Generator<std::mt19937>& random)
{
    Tree_Helper tree(Block::ID::Oak_Leaf,
                     Block::ID::Oak_Wood);

    int height      = Random::intInRange(8, 9);
    int crownSize   = Random::intInRange(4, 5);

    for (int x = -crownSize; x <= crownSize; x++)
    {
        tree.addLeaf(pos.x + x, pos.y + height, pos.z);
    }
    for (int z = -crownSize; z <= crownSize; z++)
    {
        tree.addLeaf(pos.x, pos.y + height, pos.z + z);
    }

    for (int32_t zLeaf = -1; zLeaf <= 1; zLeaf++)
    for (int32_t xLeaf = -1; xLeaf <= 1; xLeaf++)
    {
        tree.addLeaf(pos.x + xLeaf, pos.y + height - 1, pos.z + zLeaf);
        tree.addLeaf(pos.x + xLeaf, pos.y + height    , pos.z + zLeaf);
    }

    tree.addLeaf(pos.x,             pos.y + height - 1, pos.z + crownSize);
    tree.addLeaf(pos.x,             pos.y + height - 1, pos.z - crownSize);
    tree.addLeaf(pos.x + crownSize, pos.y + height - 1, pos.z );
    tree.addLeaf(pos.x - crownSize, pos.y + height - 1, pos.z );
    tree.addLeaf(pos.x,             pos.y + height + 1, pos.z );

    for (int32_t y = 1; y < height; y++)
    {
        tree.addWood(pos.x, pos.y + y, pos.z);
    }

    tree.build(access);
}






































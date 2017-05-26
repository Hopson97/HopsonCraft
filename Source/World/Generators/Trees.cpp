#include "Trees.h"

#include "../Chunk/Nodes.h"
#include "../IBlock_Accessible.h"

#include "Structures_Builder.h"

class Tree_Helper : public Structure_Builder
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
            Structure_Builder::addBlock({x, y, z, m_leafBlock});
        }

        void addAir (int x, int y, int z)
        {
            Structure_Builder::addBlock({x, y, z, Block::ID::Air});
        }

        void addWood(int x, int y, int z)
        {
            Structure_Builder::addBlock({x, y, z, m_woodBlock});
        }

        CBlock getWood()
        {
            return m_woodBlock;
        }

        CBlock getLeaf()
        {
            return m_leafBlock;
        }

    private:
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


    int y = pos.y + height;
    tree.fillXZ({pos.x - crownSize, y, pos.z - crownSize},
                {pos.x + crownSize, y, pos.z + crownSize},
                tree.getLeaf());

    tree.fillXZ({pos.x - crownSize, y - 1, pos.z - crownSize},
                {pos.x + crownSize, y - 1, pos.z + crownSize},
                tree.getLeaf());

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

    //make the tree trunk
    tree.makeColumn(pos, height, tree.getWood());

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


    //make the tree trunk
    tree.makeColumn(pos, height, tree.getWood());

    tree.build(access);
}






































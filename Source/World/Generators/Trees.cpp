#include "Trees.h"

#include "../Chunk/Nodes.h"
#include "../IBlock_Accessible.h"

#include "Structures_Builder.h"

namespace Structure
{
    class Tree_Helper : public Builder
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
                Builder::addBlock({x, y, z, m_leafBlock});
            }

            void addAir (int x, int y, int z)
            {
                Builder::addBlock({x, y, z, Block::ID::Air});
            }

            void addWood(int x, int y, int z)
            {
                Builder::addBlock({x, y, z, m_woodBlock});
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

    void makeAcaciaTree(IBlock_Accessible& access,
                        const Block::Position& pos,
                        Random::Generator<std::mt19937>& random)
    {
        Tree_Helper tree(Block::ID::Oak_Leaf,
                         Block::ID::Oak_Wood);

        auto height = random.intInRange(5, 8);
        auto width1 = random.intInRange(4, 5);
        auto dir1 = random.intInRange(0, 1);

        for (int32_t y = 1; y < height; y++)
        {
            tree.addWood(pos.x, pos.y + y, pos.z);
        }

        float y = pos.y + height;
        switch(dir1)
        {
            case 0:
                for (int32_t i = 0; i <= width1; i++)
                {
                    tree.addWood(pos.x, (int)std::floor(y), pos.z + i);
                    y += 0.5;
                }
                break;

            case 1:
                for (int32_t i = 0; i <= width1; i++)
                {
                    tree.addWood(pos.x + i, (int)std::floor(y), pos.z);
                    y += 0.5;
                }
                break;
        }

        auto dir2 = random.intInRange(0, 1);

        for (int32_t y = 1; y < height; y++)
        {
            tree.addWood(pos.x, pos.y + y, pos.z);
        }

        y = pos.y + height;
        switch(dir2)
        {
            case 0:
                for (int32_t i = 0; i <= width1; i++)
                {
                    tree.addWood(pos.x, (int)std::floor(y), pos.z + i);
                    y += 0.5;
                }
                break;

            case 1:
                for (int32_t i = 0; i <= width1; i++)
                {
                    tree.addWood(pos.x + i, (int)std::floor(y), pos.z);
                    y += 0.5;
                }
                break;
        }

        tree.build(access);
    }



}




































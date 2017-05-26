#ifndef STRUCTURES_BUILDER_H_INCLUDED
#define STRUCTURES_BUILDER_H_INCLUDED

#include "../Chunk/Nodes.h"

class IBlock_Accessible;

namespace Structure
{
    class Builder
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
            void addBlock(const Defer_Block& block);

            void fillXZ(const Block::Position& start,
                        const Block::Position& finish,
                        CBlock fill);

            void makeColumn(const Block::Position& base,
                            int height,
                            CBlock block);

            void build(IBlock_Accessible& access);

        private:
            std::vector<Defer_Block> m_deferBlocks;
    };
}

#endif // STRUCTURES_BUILDER_H_INCLUDED

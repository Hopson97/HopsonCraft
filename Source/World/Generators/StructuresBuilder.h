#ifndef StructuresBuilder_H_INCLUDED
#define StructuresBuilder_H_INCLUDED

#include <vector>
#include "../Chunk/Nodes.h"

class IBlock_Accessible;

namespace Structure
{
    class Builder
    {
        struct Defer_Block
        {
            Defer_Block(int64_t x, int64_t y, int64_t z, CBlock b)
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
                            int64_t height,
                            CBlock block);

            void build(IBlock_Accessible& access);

        private:
            std::vector<Defer_Block> m_deferBlocks;
    };
}

#endif // StructuresBuilder_H_INCLUDED

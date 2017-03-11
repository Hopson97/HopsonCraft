#include "Chunklet_File.h"

namespace
{
    std::string chunkletPositionToString(const Chunk::Chunklet_Position& p)
    {
        std::string x = std::to_string(p.x);
        std::string y = std::to_string(p.x);
        std::string z = std::to_string(p.x);

        return x + " " + y + " " + z;
    }
}

Chunklet_File::Chunklet_File(const std::string& fileName, const Chunk::Chunklet_Position& p)
{
    std::string fName = "Worlds/" + fileName + "/" + chunkletPositionToString(p) + ".CHUNK";

    m_outFile   .open(fName);
    m_inFile    .open(fName);
}

void Chunklet_File::writeBlock(const Block::Small_Position& pos, Block_t block)
{
    m_outFile << block << " " << pos.x << " " << pos.y << " " << pos.z;
}

std::unordered_map<Block::Small_Position, Block_t>
Chunklet_File::readBlocks()
{
    Block::Small_Position pos;
    Block_t block;

    while (m_inFile >> block >> pos.x >> pos.y >> pos.z)
    {

    }
}

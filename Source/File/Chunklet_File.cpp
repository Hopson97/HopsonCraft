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

Chunklet_File::Chunklet_File(const std::string& fileName, const Chunk::Chunklet_Position& p, FileMode mode)
{
    std::string fName = "Worlds/" + fileName + chunkletPositionToString(p) + ".CHUNK";

    m_fileStream.open("Temp", std::fstream::in | std::fstream::out | std::fstream::app);
}

void Chunklet_File::writeBlock(const Block::Small_Position& pos, CBlock block)
{

}

std::pair<Block::Small_Position, Block_t> Chunklet_File::getNextBlock()
{

}

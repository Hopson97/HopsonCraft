#ifndef CHUNKLET_FILE_H_INCLUDED
#define CHUNKLET_FILE_H_INCLUDED

#include "../World/Block/Block_ID.h"
#include "../World/Block/Block_Position.h"

#include "../World/Chunk/CPosition.h"
#include "../World/Chunk/CBlock.h"

#include <fstream>

enum FileMode
{
    Read,
    Write
};

class Chunklet_File
{
    Chunklet_File(const std::string& fileName, const Chunk::Chunklet_Position& p, FileMode mode);

    void writeBlock (const Block::Small_Position& pos, CBlock block);
    std::pair<Block::Small_Position, Block_t> getNextBlock();

    private:
        std::fstream m_fileStream;
};

#endif // CHUNKLET_FILE_H_INCLUDED

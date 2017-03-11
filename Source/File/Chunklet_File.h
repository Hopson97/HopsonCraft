#ifndef CHUNKLET_FILE_H_INCLUDED
#define CHUNKLET_FILE_H_INCLUDED

#include "../World/Block/Block_ID.h"
#include "../World/Block/Block_Position.h"

#include "../World/Chunk/CPosition.h"
#include "../World/Chunk/CBlock.h"

#include <fstream>
#include <unordered_map>

enum FileMode
{
    Read,
    Write
};

class Chunklet_File
{
    public:
        Chunklet_File(const std::string& fileName, const Chunk::Chunklet_Position& p);

        void writeBlock (const Block::Small_Position& pos, Block_t block);

        std::unordered_map<Block::Small_Position, Block_t>
        readBlocks ();

    private:
        std::ifstream m_inFile;
        std::ofstream m_outFile;
};

#endif // CHUNKLET_FILE_H_INCLUDED

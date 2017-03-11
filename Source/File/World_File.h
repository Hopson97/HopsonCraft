#ifndef WORLD_FILE_H_INCLUDED
#define WORLD_FILE_H_INCLUDED

#include <unordered_map>

#include "../World/Block/Block_ID.h"
#include "../World/Block/Block_Position.h"
#include "../World/Chunk/CPosition.h"

class World_File
{
    public:
        World_File(std::string&& name);

        void chunkWriteBlocks(std::unordered_map<Block::Small_Position, Block_t>& block,
                              const Chunk::Chunklet_Position& pos);


        std::unordered_map<Block::Small_Position, Block_t> chunkGetBlocks(const Chunk::Chunklet_Position& pos);

    private:
        std::string m_baseName;
};

#endif // WORLD_FILE_H_INCLUDED

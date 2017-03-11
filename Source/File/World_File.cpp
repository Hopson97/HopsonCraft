#include "World_File.h"

#include <fstream>

World_File::World_File(std::string&& name)
:   m_baseName  (std::move(name))
{

}

void World_File::create()
{

}

void
World_File::chunkWriteBlocks(std::unordered_map<Block::Small_Position, Block_t>& block,
                             const Chunk::Chunklet_Position& pos)
{

}

std::unordered_map<Block::Small_Position, Block_t>
World_File::chunkGetBlocks(const Chunk::Chunklet_Position& pos)
{

}

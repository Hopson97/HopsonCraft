#include "World_File.h"

#include <fstream>

#include "Chunklet_File.h"

#ifdef linux
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
#elif _WIN32
    #include <windows.h>
#endif

namespace Directory
{
    void create(const std::string& folderName)
    {
        #ifdef linux
            mkdir(folderName.c_str(), 0700);
        #elif _WIN32
            CreateDirectory(folderName.c_str(), nullptr);
        #endif
    }
}


World_File::World_File(std::string&& name)
:   m_baseName  (std::move(name))
{
    Directory::create("Worlds/" + m_baseName);
}

void
World_File::chunkWriteBlocks(std::unordered_map<Block::Small_Position, Block_t>& block,
                             const Chunk::Chunklet_Position& pos)
{
    Chunklet_File file(m_baseName, pos);
    for (auto& b : block)
    {
        file.writeBlock(b.first, b.second);
    }
}

std::unordered_map<Block::Small_Position, Block_t>
World_File::chunkGetBlocks(const Chunk::Chunklet_Position& pos)
{
    Chunklet_File file(m_baseName, pos);
    return file.readBlocks();
}

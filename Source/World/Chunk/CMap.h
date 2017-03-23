#ifndef CMAP_H_INCLUDED
#define CMAP_H_INCLUDED

#include <unordered_map>
#include <memory>

#include "CSection.h"
#include "CFull_Chunk.h"

namespace Chunk
{
    struct Map
    {
        ///@TODO Make this private
        std::unordered_map<Chunk::Position, std::unique_ptr<Full_Chunk>> m_chunks;

        void addChunk(const Chunk::Position& position, World& world);

        Section* get    (const Chunk::Chunklet_Position& position);
        bool existsAt   (const Chunk::Chunklet_Position& position);
    };
}

#endif // CMAP_H_INCLUDED

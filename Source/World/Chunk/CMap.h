#ifndef CMAP_H_INCLUDED
#define CMAP_H_INCLUDED

#include <unordered_map>
#include <memory>

#include "CSection.h"

namespace Chunk
{
    struct Map
    {
        std::unordered_map<Chunk::Chunklet_Position, std::unique_ptr<Section>> m_chunks;

        Section* get    (const Chunk::Chunklet_Position& position);
        bool existsAt   (const Chunk::Chunklet_Position& position);
    };
}

#endif // CMAP_H_INCLUDED

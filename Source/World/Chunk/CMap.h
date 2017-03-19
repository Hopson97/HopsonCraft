#ifndef CMAP_H_INCLUDED
#define CMAP_H_INCLUDED

#include <unordered_map>
#include <memory>

#include "CSection.h"

namespace Chunk
{
    struct Map
    {
        std::unordered_map<Chunk::Position, std::unique_ptr<Section>> m_chunks;

        Section* get    (const Chunk::Position& position);
        bool existsAt   (const Chunk::Position& position);
    };
}

#endif // CMAP_H_INCLUDED

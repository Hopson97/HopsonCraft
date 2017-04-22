#ifndef CBOUNDSCHECK_H_INCLUDED
#define CBOUNDSCHECK_H_INCLUDED

#include <cstdint>

#include "../Block/Block_Position.h"

namespace Chunk
{
    class Section;
    class Map;

    Section* getSection(Block::Small_Position& position,
                        Section*    defaultSection,
                        Map&        chunkMap);

    const Section* getConstSection(Block::Small_Position& position,
                                   const Section*   defaultSection,
                                   Map&       chunkMap);
}

#endif // CBOUNDSCHECK_H_INCLUDED

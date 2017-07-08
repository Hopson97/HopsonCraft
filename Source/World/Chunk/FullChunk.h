#ifndef FullChunk_H_INCLUDED
#define FullChunk_H_INCLUDED

#include <vector>
#include <cstdint>

#include "Section.h"

namespace Chunk
{
    class FullChunk
    {
        public:
            int64_t getX() const;
            int64_t getZ() const;

        private:
            std::vector<Section> m_sections;

            Section* getSection(int64_t blockY);

            int64_t m_xPosition,
                    m_zPosition;
    };
}

#endif // FullChunk_H_INCLUDED

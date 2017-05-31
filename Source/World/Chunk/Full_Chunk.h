#ifndef FULL_CHUNK_H_INCLUDED
#define FULL_CHUNK_H_INCLUDED

#include <vector>
#include <cstdint>

#include "Section.h"

namespace Chunk
{
    class Full_Chunk
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

#endif // FULL_CHUNK_H_INCLUDED

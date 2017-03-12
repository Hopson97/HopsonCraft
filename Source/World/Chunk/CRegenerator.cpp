#include "CRegenerator.h"

namespace Chunk
{
    void Regenerator::addChunklet(Chunklet& chunklet)
    {
        if (m_chunklets.find(chunklet.getPosition()) == m_chunklets.end())
        {
            //chunklet.queueForBuffer();
            m_chunklets.insert(std::make_pair(chunklet.getPosition(), &chunklet));
        }
    }

    void Regenerator::addChunklets(std::vector<Chunklet*>chunklets)
    {
        for (Chunklet* c : chunklets)
        {
            addChunklet(*c);
        }
    }

    void Regenerator::regen()
    {
        while (!m_chunklets.empty())
        {
            Chunklet& c = *(*m_chunklets.begin()).second;
            c.createMesh();
            c.bufferMesh();
            m_chunklets.erase(m_chunklets.begin());
        }
    }
}

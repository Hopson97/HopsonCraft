#ifndef MASTER_H_INCLUDED
#define MASTER_H_INCLUDED

#include "RChunk.h"

class Chunklet;
struct Camera;

namespace Renderer
{
    class Master
    {
        public:
            void clear();

            void update(const Camera& camera);
            void draw(const Chunklet& chunklet);

        private:
            RChunk m_chunkRenderer;
    };
}

#endif // MASTER_H_INCLUDED

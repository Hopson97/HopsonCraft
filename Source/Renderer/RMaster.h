#ifndef MASTER_H_INCLUDED
#define MASTER_H_INCLUDED

#include "RSimple.h"
#include "RChunk.h"

class Quad;
class Chunklet;
struct Camera;

namespace Renderer
{
    class Master
    {
        public:
            void clear();

            void update(const Camera& camera);

            void draw(const Quad& model);
            void draw(const Chunklet& chunklet);

        private:
            Simple m_simpleRenderer;
            RChunk m_chunkRenderer;
    };
}

#endif // MASTER_H_INCLUDED

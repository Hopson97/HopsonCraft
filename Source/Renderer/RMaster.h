#ifndef MASTER_H_INCLUDED
#define MASTER_H_INCLUDED

#include "RSFML.h"
#include "RChunk.h"
#include "RLiquid.h"


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
            void draw(const sf::Drawable& drawable);

        private:
            RSFML   m_sfmlRenderer;
            RChunk  m_chunkRenderer;
            RLiquid m_liquidRenderer;
    };
}

#endif // MASTER_H_INCLUDED

#ifndef MASTER_H_INCLUDED
#define MASTER_H_INCLUDED

#include "RSFML.h"
#include "RSolid.h"
#include "RSimple.h"


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
            void draw(const Quad& quad);

        private:
            RSFML   m_sfmlRenderer;
            RChunk  m_chunkRenderer;
            RSimple m_simpleRenderer;

    };
}

#endif // MASTER_H_INCLUDED

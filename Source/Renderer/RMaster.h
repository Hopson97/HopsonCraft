#ifndef MASTER_H_INCLUDED
#define MASTER_H_INCLUDED

#include "RSFML.h"
#include "RSolid.h"
#include "RSimple.h"
#include "RFlora.h"
#include "RLiquid.h"
#include "RHit_Box.h"

namespace Chunk
{
    class Section;
}

struct Camera;

namespace Renderer
{
    class Master
    {
        public:
            void clear();

            void update(const Camera& camera);

            void draw(const Vector3& location);
            void draw(const Chunk::Section& section);
            void draw(const sf::Drawable& drawable);
            void draw(const Quad& quad);

        private:
            RSFML       m_sfmlRenderer;
            RSimple     m_simpleRenderer;

            RChunk      m_chunkRenderer;
            RFlora      m_floraRenderer;
            RLiquid     m_liquidRenderer;
            RHit_Box    m_hitboxRenderer;


    };
}

#endif // MASTER_H_INCLUDED

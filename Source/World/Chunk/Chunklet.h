#ifndef CHUNKLET_H_INCLUDED
#define CHUNKLET_H_INCLUDED

#include <array>
#include <atomic>

#include "../../Glm_Common.h"

#include "../Block/Block_ID.h"
#include "../World_Constants.h"

#include "CMesh.h"
#include "CBlock.h"

#include "../Block/Block_Position.h"
#include "CPosition.h"

#include "../../Entity.h"

namespace Chunk
{
    class Map;
}

namespace Texture
{
    class Atlas;
}

class Chunklet : private Entity
{
    struct CFlags
    {
        bool hasFaces     = false;
        bool hasMesh      = false;
        bool hasBuffered  = false;
    };

    public:
        Chunklet(const Chunk::Chunklet_Position& pos,
                 Chunk::Map& map);

        void createMesh();
        void bufferMesh();

        void qSetBlock(const Block::Small_Position& pos, CBlock block);

        CBlock getBlock (const Block::Small_Position& pos) const;
        CBlock qGetBlock(const Block::Small_Position& pos) const;

        const Chunk::Mesh& getMesh() const;
        const Matrix4& getMat() const;

        const Chunk::Chunklet_Position& getPosition() const;

        void setFaces(bool faces);
        const CFlags& getFlags() { return m_flags; }

    private:

        uint32_t getBlockIndex (const Block::Small_Position& pos) const;

        std::array<CBlock, World_Constants::CH_VOLUME> m_blocks;

        Matrix4 m_modelMat;
        Chunk::Mesh m_mesh;
        Chunk::Chunklet_Position m_pos;

        Chunk::Map* m_p_chunkMap;

        CFlags m_flags;
};

#endif // CHUNKLET_H_INCLUDED

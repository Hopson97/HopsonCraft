#ifndef CHUNKLET_H_INCLUDED
#define CHUNKLET_H_INCLUDED

#include <array>

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
    public:
        Chunklet(const Chunk::Chunklet_Position& pos,
                 Chunk::Map& map);

        void createMesh();

        CBlock getBlock (const Block::Position& pos) const;
        CBlock qGetBlock(const Block::Position& pos) const;

        const Chunk::Mesh& getMesh() const;
        const Matrix4& getMat() const;

        const Chunk::Chunklet_Position& getPosition() const;

    private:

        uint32_t getBlockIndex (const Block::Position& pos) const;

        std::array<CBlock, World_Constants::CH_VOLUME> m_blocks;

        Matrix4 m_modelMat;
        Chunk::Mesh m_mesh;
        Chunk::Chunklet_Position m_pos;

        Chunk::Map* m_p_chunkMap;
};

#endif // CHUNKLET_H_INCLUDED

#ifndef CCOLUMN_H_INCLUDED
#define CCOLUMN_H_INCLUDED

#include <vector>
#include <memory>
#include <cstdint>
#include <queue>

#include "Chunklet.h"
#include "CBlock.h"
#include "../Block/Block_Position.h"
#include "../../Temp/Noise_Generator.h"

#include "../../Physics/AABB.h"

class World_File;

namespace Renderer
{
    class Master;
}

namespace Chunk
{
    class Map;
    class Regenerator;

    class Column
    {
        struct CFlags
        {
            CFlags()
            :   hasFullMesh (false)
            ,   hasBuffered (false)
            ,   deleteMe    (false)
            ,   generated   (false) {}

            std::atomic<bool> hasFullMesh;
            std::atomic<bool> hasBuffered;
            std::atomic<bool> deleteMe;
            std::atomic<bool> generated;
        };


        public:
            Column(const Position& pos, Map& map, Regenerator& regenerator, World_File& file);

            void createFullMesh();

            void update();
            bool draw(Renderer::Master& renderer, bool tryBuffer);
            const Position& getPosition() const;



            void    setBlock    (const Block::Column_Position& pos, CBlock block);
            CBlock  getBlock    (const Block::Column_Position& pos) const;

            Chunklet* getChunklet(int32_t index);

            const CFlags& getFlags();
            void setDeleteFlag(bool deleteF);

            const Vector3& getWorldPosition() const;
            const AABB&    getAABB() const;

        private:
            void generate();

            std::pair<int32_t, int32_t> getChunkletBlockLocation(const Block::Column_Position& pos) const;

            Chunklet* getChunkletnc(int32_t index);
            void addChunklet();

            std::vector<std::unique_ptr<Chunklet>> m_chunklets;

            Position    m_position;
            Vector3     m_worldPosition;


            Map*            m_p_chunkMap    = nullptr;
            Regenerator*    m_p_regenerator = nullptr;
            World_File*     m_p_worldFile   = nullptr;

            AABB        m_box;

            int32_t m_chunkCount = 0;

            CFlags m_flags;


    };
}

#endif // CCOLUMN_H_INCLUDED

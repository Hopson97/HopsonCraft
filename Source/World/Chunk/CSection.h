#ifndef CSECTION_H_INCLUDED
#define CSECTION_H_INCLUDED

#include <array>

#include "../World_Constants.h"

#include "CPosition.h"
#include "CBlock.h"
#include "CMesh_Builder.h"
#include "../Block/Block_Database.h"

namespace Chunk
{
    class Map;

    class Section
    {
        //This struct helps with optimizing the creation of the mesh
        struct Layer
        {
            int16_t opaqueCount = 0;

            void update(CBlock block)
            {
                const Block::Data_Holder& data = Block::Database::get().getBlock(block.id).getData().get();
                data.isOpaque ?
                    opaqueCount++ :
                    opaqueCount--;
            }
        };

        public:
            Section(const Chunklet_Position& position, Map& map);

            //Blocks getters/ Setters
            //with bounds checking
            void    setBlock(Block::Small_Position& position, CBlock block);
            CBlock  getBlock(Block::Small_Position& position) const;
            //with no bounds checking
            void    qSetBlock(const Block::Small_Position& position, CBlock block);
            CBlock  qGetBlock(const Block::Small_Position& position) const;

            //Natural lights getters/ setters
            //with bounds checking
            void setNaturalLight(Block::Small_Position& position, uint8_t value);
            uint8_t getNaturalLight(Block::Small_Position& position) const;
            //with no bounds checking
            void qSetNaturalLight(const Block::Small_Position& position, uint8_t value);
            uint8_t qGetNaturalLight(const Block::Small_Position& position) const;

            //Block lights getters/ setters
            //with bounds checking
            void setBlockLight(Block::Small_Position& position, uint8_t value);
            uint8_t getBlockLight(Block::Small_Position& position) const;
            //with no bounds checking
            void qSetBlockLight(const Block::Small_Position& position, uint8_t value);
            uint8_t qGetBlockLight(const Block::Small_Position& position) const;

            //@TODO move to .cpp file
            const Chunklet_Position& getPosition()  const   { return m_position;        }
            const Meshes& getMeshes()               const   { return m_meshes;          }
            const Layer& getLayer(int8_t y)         const   { return m_layerHasAir[y];  }


        private:
            Section* getSection(Block::Small_Position& position);
            const Section* getConstSection(Block::Small_Position& position) const;

            void checkBound(int8_t& dir, int32_t& change) const;

            uint32_t getIndexFrom(const Block::Small_Position& position) const;

            std::array<CBlock, CHUNK_VOLUME>    m_blocks;
            std::array<CLight, CHUNK_VOLUME>    m_light;
            std::array<Layer, CHUNK_SIZE>       m_layerHasAir;

            Chunklet_Position m_position;

            Mesh_Builder m_meshBuilder;
            Meshes       m_meshes;

            Map* mp_chunks;
    };
}

#endif // CSECTION_H_INCLUDED

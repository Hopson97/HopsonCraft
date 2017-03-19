#ifndef CSECTION_H_INCLUDED
#define CSECTION_H_INCLUDED

#include <array>

#include "../World_Constants.h"

#include "CPosition.h"
#include "CBlock.h"
#include "CMesh_Builder.h"

namespace Chunk
{
    class Section
    {
        public:
            Section(const Chunklet_Position& position);

            //Blocks getters/ Setters
            //with bounds checking
            void    setBlock(const Block::Small_Position& position, CBlock block);
            CBlock  getBlock(const Block::Small_Position& position) const;
            //with no bounds checking
            void    qSetBlock(const Block::Small_Position& position, CBlock block);
            CBlock  qGetBlock(const Block::Small_Position& position) const;

            //Natural lights getters/ setters
            //with bounds checking
            void setNaturalLight(const Block::Small_Position& position, uint8_t value);
            uint8_t getNaturalLight(const Block::Small_Position& position) const;
            //with no bounds checking
            void qSetNaturalLight(const Block::Small_Position& position, uint8_t value);
            uint8_t qGetNaturalLight(const Block::Small_Position& position) const;

            //Block lights getters/ setters
            //with bounds checking
            void setBlockLight(const Block::Small_Position& position, uint8_t value);
            uint8_t getBlockLight(const Block::Small_Position& position) const;
            //with no bounds checking
            void qSetBlockLight(const Block::Small_Position& position, uint8_t value);
            uint8_t qGetBlockLight(const Block::Small_Position& position) const;

            //@TODO move to .cpp file
            const Chunklet_Position& getPosition() const { return m_position; }
            const Meshes& getMeshes() const { return m_meshes; }


        private:
            Section* getSection(const Block::Small_Position& position);
            const Section* getConstSection(const Block::Small_Position& position) const;
            void     checkBound(int8_t dir, int32_t& change) const;

            uint32_t getIndexFrom(const Block::Small_Position& position) const;

            std::array<CBlock, CHUNK_VOLUME>    m_blocks;
            std::array<CLight, CHUNK_VOLUME>    m_light;
            std::array<bool, CHUNK_SIZE>        m_layerHasAir;

            Chunklet_Position m_position;

            Mesh_Builder m_meshBuilder;
            Meshes       m_meshes;
    };
}

#endif // CSECTION_H_INCLUDED

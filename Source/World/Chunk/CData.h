#ifndef CDATA_H_INCLUDED
#define CDATA_H_INCLUDED

#include "../../Util/Array3D.h"
#include "../World_Constants.h"
#include "CNodes.h"

/*
    As of 04/05/2017, this class is unused (for now)
*/

namespace Chunk
{
    class Data
    {
        public:
            //Blocks getters/ Setters
            //with bounds checking
            void    setBlock(Block::Position& position, CBlock block);
            CBlock  getBlock(Block::Position& position) const;
            //with no bounds checking
            void    qSetBlock(const Block::Position& position, CBlock block);
            CBlock  qGetBlock(const Block::Position& position) const;

            //Natural lights getters/ setters
            //with bounds checking
            void setNaturalLight(Block::Position& position, uint8_t value);
            uint8_t getNaturalLight(Block::Position& position) const;
            //with no bounds checking
            void qSetNaturalLight(const Block::Position& position, uint8_t value);
            uint8_t qGetNaturalLight(const Block::Position& position) const;

            //Block lights getters/ setters
            //with bounds checking
            void setBlockLight(Block::Position& position, uint8_t value);
            uint8_t getBlockLight(Block::Position& position) const;
            //with no bounds checking
            void qSetBlockLight(const Block::Position& position, uint8_t value);
            uint8_t qGetBlockLight(const Block::Position& position) const;


        private:
            Array3D<CBlock, CHUNK_SIZE>     m_blocks;
            Array3D<CLight, CHUNK_SIZE>     m_light;
    };
}

#endif // CDATA_H_INCLUDED

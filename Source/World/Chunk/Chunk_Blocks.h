#ifndef CHUNK_BLOCKS_H
#define CHUNK_BLOCKS_H

#include <vector>
#include <unordered_map>
#include <cstdint>
#include "../Block/Block_Location.h"

#include "Chunk_Location.h"
#include "Chunk_Layer.h"
#include "../Block/Block_Enums.h"

class Chunk_Map;
class Chunk;

class Chunk_Blocks
{
    public:
        Chunk_Blocks(const Chunk& chunk,
                     const Chunk_Location& location,
                     Chunk_Map& chunkMap);

        void setBlock   (const Block_Location& location,
                         uint8_t block,
                         bool overrideBlocks = true);

        void qSetBlock  (const Block_Location& location,
                         uint8_t block,
                         bool overrideBlocks = true);

        const Block::Block_Type& getBlock (const Block_Location& location) const;


        void addBlock(const Block_Location& location, uint8_t block);
        const std::unordered_map<Block_Location, uint8_t>& getAddedBlocks() const;

        size_t getLayerCount() const;

        int getMaxheightAt (int x, int z) const;
        void setMaxHeight  (const Block_Location& location);

        const Chunk_Layer& getLayer     (uint32_t layer) const;
        bool layerHasTranslucentBlocks  (uint32_t layer) const;

        void setMaxHeights (const std::vector<int>& heightMap);

    private:
        const Block::Block_Type& getAdjacentChunkBlock (int xChange,
                                                        int zChange,
                                                        const Block_Location& location) const;

        void addLayers (unsigned target);

        const Chunk* m_p_chunk;
        Chunk_Location m_location;
        Chunk_Map* m_p_chunkMap;

        std::vector<Chunk_Layer> m_layers;
        std::unordered_map<Block_Location, uint8_t> m_addedBlocks;

        std::vector<int> m_maxHeights;
};

#endif // CHUNK_BLOCKS_H

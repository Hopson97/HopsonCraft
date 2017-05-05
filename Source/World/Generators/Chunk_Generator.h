#ifndef CHUNK_GENERATOR_H_INCLUDED
#define CHUNK_GENERATOR_H_INCLUDED

#include <vector>
#include <mutex>

#include "../../Util/Random.h"
#include "../../Util/Array2D.h"

#include "../../Temp/Noise_Generator.h"

#include "../Block/Block_Position.h"
#include "../Block/Block_ID.h"

#include "../World_Constants.h"



namespace Chunk
{
    class Full_Chunk;
}

class World_Settings;

class Chunk_Generator
{
    public:
        Chunk_Generator(const World_Settings& worldSettings);

        void generateBlocksFor(Chunk::Full_Chunk& chunk);

    private:
        Block::ID getBlock  (const Block::Position& pos);
        void setTopBlock    (const Block::Position& pos, Block::ID& id);

        void setRandomSeed();
        void makeHeightMap();

        //Generators
        Random::Generator<std::mt19937> m_randomGenerator;
        Noise::Generator m_noiseGenerator;

        //Containers
        std::vector<Block::Position>    m_oakTreeLocations;
        Array2D<uint32_t, CHUNK_AREA>   m_heightMap;

        //Etc
        const World_Settings* m_pWorldSettings;
        int m_maxHeight = 0;

        Chunk::Full_Chunk* m_pChunk;

        std::mutex m_genMutex;
};

#endif // CHUNK_GENERATOR_H_INCLUDED

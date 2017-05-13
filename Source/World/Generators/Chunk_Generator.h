#ifndef CHUNK_GENERATOR_H_INCLUDED
#define CHUNK_GENERATOR_H_INCLUDED

#include <vector>
#include <mutex>
#include <map>

#include "../../Util/Random.h"
#include "../../Util/Array2D.h"

#include "../../Temp/Noise_Generator.h"

#include "../Block/Block_Position.h"
#include "../Block/Block_ID.h"

#include "../World_Constants.h"

#include "../Chunk/CNodes.h"



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
        void makeSuperFlatWorld ();
        void makeRegularWorld   ();

        Block::ID getBlock  (const Block::Position& pos);
        void setTopBlock    (const Block::Position& pos, Block::ID& id);

        void setRandomSeed  ();
        void makeAdvancedHeigtMap();
        void makeHeightMap  ();
        void makeBiomeMap   ();
        void reset();

        //Containers
        std::vector<Block::Position>                    m_oakTreeLocations;
        std::vector<std::pair<Block::Position, CBlock>> m_littleBlockLoc;
        Array2D<int, CHUNK_AREA + 1> m_biomeMap;
        Array2D<int, CHUNK_AREA>     m_heightMap;


        //Generators
        Random::Generator<std::mt19937> m_randomGenerator;
        Noise::Generator m_noiseGenerator;
        Noise::Generator m_biomeNoise;

        const World_Settings* m_pWorldSettings;
        int m_maxHeight = 0;

        Chunk::Full_Chunk* m_pChunk;

        std::mutex m_genMutex;
};

#endif // CHUNK_GENERATOR_H_INCLUDED

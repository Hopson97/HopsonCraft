#ifndef Terrain_Generator_H_INCLUDED
#define Terrain_Generator_H_INCLUDED

#include <vector>
#include <mutex>
#include <map>

#include "../../Util/Random.h"
#include "../../Util/Array2D.h"

#include "../../Temp/Noise_Generator.h"

#include "../Block/Block_Position.h"
#include "../Block/Block_ID.h"

#include "../World_Constants.h"

#include "../Chunk/Nodes.h"

#include "Generation_Type.h"



namespace Chunk
{
    class Full_Chunk;
}

class World_Settings;
class World_File;

class Terrain_Generator
{
    public:
        Terrain_Generator(const World_Settings& worldSettings);

        void generateBlocksFor(Chunk::Full_Chunk& chunk, World_File& worldFile);

    private:
        void makeSuperFlatWorld ();
        void makeRegularWorld   ();

        Block::ID getBlock      (const Block::Position& pos);
        void setTopBlock        (const Block::Position& pos, Block::ID& id);

        void setRandomSeed      ();
        void makeHeightSection  (int xMin, int xMax, int yMin, int yMax);
        void makeHeightMap      ();
        void makeBiomeMap       ();
        void reset              ();

        World_Generation_Type m_worldGenType;

        //Containers
        std::vector<std::pair<Block::Position, Structure::ID>>   m_oakTreeLocations;
        std::vector<std::pair<Block::Position, CBlock>>         m_littleBlockLoc;
        Array2D<int, CHUNK_AREA_P>    m_biomeMap;
        Array2D<int, CHUNK_AREA_P>    m_heightMap;

        //Generators
        Random::Generator<std::mt19937> m_randomGenerator;
        Noise::Generator m_heightGen;
        Noise::Generator m_biomeNoise;

        const World_Settings* m_pWorldSettings;
        int m_maxHeight = 0;

        Chunk::Full_Chunk* m_pChunk;

        std::mutex m_genMutex;
};

#endif // Terrain_Generator_H_INCLUDED

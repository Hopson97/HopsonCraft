#ifndef Terrain_H_INCLUDED
#define Terrain_H_INCLUDED

#include <vector>
#include <mutex>
#include <map>

#include "../../Util/Random.h"
#include "../../Util/Array2D.h"

#include "Noise.h"

#include "../Block/BlockPosition.h"
#include "../Block/BlockID.h"

#include "../WorldConstants.h"

#include "../Chunk/Nodes.h"

#include "GenerationType.h"


/*
namespace Chunk
{
    class FullChunk;
}

class WorldSettings;
class World_File;

class Terrain
{
    public:
        Terrain(const WorldSettings& worldSettings);

        void generateBlocksFor(Chunk::FullChunk& chunk, World_File& worldFile);

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

        World_GenerationType m_worldGenType;

        //Containers
        std::vector<std::pair<Block::Position, Structure::ID>>   m_oakTreeLocations;
        std::vector<std::pair<Block::Position, CBlock>>         m_littleBlockLoc;
        Array2D<int, CHUNK_AREA_P>    m_biomeMap;
        Array2D<int, CHUNK_AREA_P>    m_heightMap;

        //Generators
        Random::Generator<std::mt19937> m_randomGenerator;
        Noise::Generator m_heightGen;
        Noise::Generator m_biomeNoise;

        const WorldSettings* m_pWorldSettings;
        int m_maxHeight = 0;

        Chunk::FullChunk* m_pChunk;

        std::mutex m_genMutex;
};
*/
#endif // Terrain_H_INCLUDED

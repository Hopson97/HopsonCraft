#ifndef WORLD_GENERATOR_H_INCLUDED
#define WORLD_GENERATOR_H_INCLUDED

#include <mutex>
#include <vector>
#include <thread>

#include "../../Glm_Common.h"
#include "../Chunk/CPosition.h"

/*
    This is basically an extension for the world class.
    It generates chunks and builds meshes on a concurrent thread.

    It feels kinda bad that there are so many pointers, but hey-ho,
    that's why re-factoring is a thing ;)

    However, usage of this class seems to cause a crash on world exit,
    as opposed to it working just fine in the World class.
    **************************
    **  @TODO ^ Fix that    **
    **************************

    The reason behind this class is so I can make the world gen code
    neater without bloating the heck out of the World class.
*/

namespace Chunk
{
    class Map;
}

class World_Settings;
class Camera;

class World_Generator
{
    public:
        World_Generator(Chunk::Map&             chunkMap,
                        std::mutex&             deleteMutex,
                        const World_Settings&   settings,
                        const Camera&           camera,
                        std::vector<Chunk::Position>& deleteChunks);

        ~World_Generator();

        void launch();

    private:
        void generateWorld();

        std::vector<std::thread>    m_workers;

        const Camera*                   m_pCamera           = nullptr;
        const World_Settings*           m_pWorldSettings    = nullptr;
        Chunk::Map*                     m_pChunkMap         = nullptr;
        std::mutex*                     m_pDeleteMutex      = nullptr;
        std::vector<Chunk::Position>*   m_pDeleteChunks     = nullptr;

        int     m_loadingDistance = 1;
        bool    m_isRunning = true;

};

#endif // WORLD_GENERATOR_H_INCLUDED

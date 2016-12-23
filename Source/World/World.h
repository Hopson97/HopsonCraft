#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <memory>
#include <cstdint>

#include "../Player/Player.h"
#include "Chunk/Chunk_Location.h"
#include "Chunk/Chunk_Map.h"

namespace sf
{
    class Event;
}

class Master_Renderer;

class World
{
    public:
        World(uint32_t seed,
              const std::string& name);

        void input  (sf::Event& e);
        void input  ();
        void update (float dt);
        void draw   (Master_Renderer& renderer);

    private:
        Player          m_player;
        Chunk_Location  m_playerLocation;

        std::string     m_name;
        Chunk_Map       m_chunkMap;

    public:
        constexpr static uint16_t   CHUNK_SIZE      = 20,    //Width/ depth of a chunk, height is infinite
                                    WATER_LEVEL     = 90,
                                    BEACH_LEVEL     = WATER_LEVEL + 4,
                                    SNOW_LEVEL      = 250;
};

#endif // WORLD_H_INCLUDED

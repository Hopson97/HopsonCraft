#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <vector>

#include "Chunk/Chunk_Map.h"
#include "../Crosshair.h"
#include "../Player/Player.h"


namespace sf
{
    class Event;
}

class Master_Renderer;
class Camera;
class Application;

class World
{
    public:
        World(uint32_t seed,
              const std::string& name);

        void input      (const sf::Event& e);
        void input      ();
        void update     (float dt, Camera& camera);
        void draw       (float dt, Master_Renderer& renderer);
        void drawXHair  (Master_Renderer& renderer);

        const Chunk_Map&    getChunkMap ()  const;
        const Player&       getPlayer   ()  const;

        void save() const;

    private:
        void blockRayHit();
        void blockEdit  (const Vector3& lastRayPos, const Vector3& rayPos);

        void loadWorldFile();

        std::shared_ptr<Player> m_player;
        Chunk_Location  m_playerLocation;

        std::string     m_name;
        Chunk_Map       m_chunkMap;
        Crosshair       m_crosshair;
        uint32_t        m_seed;

    public:
        constexpr static uint16_t   CHUNK_SIZE      = 20,    //Width/ depth of a chunk, height is infinite
                                    WATER_LEVEL     = 90,
                                    BEACH_LEVEL     = WATER_LEVEL + 4,
                                    SNOW_LEVEL      = 250;
};

#endif // WORLD_H_INCLUDED

#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <vector>

#include "Chunk/Chunk_Map.h"
#include "../Crosshair.h"
#include "../Mob/Player.h"


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

        void save();

        void makeExplosion(const Vector3& worldPosition, int power);

    private:
        void blockRayHit();
        void blockEdit  (const Vector3& lastRayPos, const Vector3& rayPos);

        void loadWorldFile();

        std::string     m_name;

        Player          m_player;
        Chunk_Map       m_chunkMap;
        Crosshair       m_crosshair;
        uint32_t        m_seed;
};

#endif // WORLD_H_INCLUDED

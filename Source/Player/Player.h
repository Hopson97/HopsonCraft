#ifndef PLAYER_H
#define PLAYER_H

#include "../World/Block/Block_Type/Block_Type.h"
#include "../Camera.h"
#include "../Mob/Mob_Base.h"
#include "../World/Chunk/Chunk_Location.h"

class Chunk_Map;
class Camera;
class ChunkMap;

namespace sf
{
    class Event;
}

class Player : public Mob
{
    public:
        Player(Chunk_Map& chunkMap);

        void setPosition(const Vector3& position);

        void input      (const sf::Event& e);
        void input      (Camera& camera);
        void onUpdate   (float dt) override;

        const Block::Block_Type& getBlock() const;

        constexpr static double SPEED = 0.45;

        const Chunk_Location& getChunkLocation() const;

    private:
        void changeBlock (int increment);

        const Block::Block_Type*    m_p_heldBlock;
        Chunk_Map*                  m_p_chunkMap    = nullptr;
        Chunk_Location              m_chunkLocation;
};

#endif // PLAYER_H

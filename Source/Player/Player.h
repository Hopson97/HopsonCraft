#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity/Entity.h"
#include "../World/Block/Block.h"

class Chunk_Map;

namespace sf
{
    class Event;
}

class Player
{
    public:
        Player();

        const Entity& getCamera () const;

        void setPosition(const Vector3& position);

        void input (const sf::Event& e);
        void input ();
        void update (float dt, Entity& camera, Chunk_Map& chunkMap);

        const Block_t& getBlock() const;

        constexpr static double SPEED = 0.45;


    private:
        void translationInput   ();
        void walkingInput (Vector3& change, float yaw);
        void upDownInput (Vector3& change);

        void rotationInput ();

        void changeBlock (int increment);

        void collision(Chunk_Map& chunkMap, float dt);

        Entity  m_camera;
        Vector3 m_velocity;
        const Block_t* m_p_heldBlock;

        bool m_isOnGround = true;
};

#endif // PLAYER_H

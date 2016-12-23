#ifndef PLAYER_H
#define PLAYER_H

#include "../World/Block/Block_Data.h"
#include "../Camera.h"

class Chunk_Map;

namespace sf
{
    class Event;
}

class Player
{
    public:
        Player();

        const Camera& getCamera() const;

        void setPosition(const Vector3& position);

        void input (const sf::Event& e);
        void input ();
        void update (float dt, Camera& camera, Chunk_Map& chunkMap);

        const Block::Block_Data& getBlock() const;

        constexpr static double SPEED = 0.45;


    private:
        void translationInput   ();
        void walkingInput (Vector3& change, float yaw);
        void upDownInput (Vector3& change);

        void rotationInput ();

        void changeBlock (int increment);

        void collision(Chunk_Map& chunkMap, float dt);

        Vector3 m_velocity;
        const Block::Block_Data* m_p_heldBlock;

        bool m_isOnGround = true;

        Camera m_camera;
};

#endif // PLAYER_H

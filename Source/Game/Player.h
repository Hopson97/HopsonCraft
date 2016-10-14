#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>

#include "OpenGL/Glm/glm_transformations.h"
#include "Camera.h"
#include "Vector.h"
#include "Chunk/Chunk.h"
#include "AABB.h"
#include "Vector.h"

#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player( std::unordered_map<Vector2i, Chunk_Ptr>& chunkMap );

        void update ( float dt );

        const Camera& getCamera () const;

        const Vector2i& getChunkLocation () const;


        constexpr static float ACC = 0.45;

    private:
        const Vector3   getBlockPositionInChunk () const;

        void input              ( float dt );
        void getCurrentChunk    ();

        void setAABB            ();


        Vector3 m_velocity;

        Camera m_camera;

        std::unordered_map<Vector2i, Chunk_Ptr>* m_p_chunks = nullptr;
        Chunk* m_currentChunk = nullptr;

        AABB m_aabb;

        sf::Clock m_lockTimer;
        bool m_isLocked = false;
};

#endif // PLAYER_H

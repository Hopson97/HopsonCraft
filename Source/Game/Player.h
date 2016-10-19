#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>

#include "OpenGL/Glm/glm_transformations.h"
#include "Camera.h"
#include "Vector.h"
#include "Chunk/Chunk.h"
#include "AABB.h"
#include "Vector.h"
#include "Toggle_Key.h"

#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player( std::unordered_map<Vector2i, Chunk_Ptr>& chunkMap );

        void update ( float dt );

        const Camera&   getCamera   () const;
        const Vector3&  getPosition () const;
        const Vector3&  getRotation () const;

        constexpr static float ACC = 0.3;

    private:
        void input              ( float dt );
        void getCurrentChunk    ();

        void setAABB    ();
        void collide    ();

        std::unordered_map<Vector2i, Chunk_Ptr>* m_p_chunks = nullptr;
        Chunk* m_p_currentChunk = nullptr;


        AABB m_bottomAABB;


        Vector3 m_velocity;

        Camera m_camera;

        bool m_isLocked     = false;
        bool m_isFlyMode    = true;

        std::vector<Toggle_Key> m_toggles;
};

#endif // PLAYER_H

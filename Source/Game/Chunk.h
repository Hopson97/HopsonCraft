#ifndef CHUNK_H
#define CHUNK_H

#include <map>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "OpenGL/Glm/glm_transformations.h"
#include "Vector.h"
#include "Model.h"
#include "Entity.h"

namespace Block
{
    class Block_Base;
}

class Texture_Atlas;

class Chunk;
typedef std::unique_ptr<Chunk> Chunk_Ptr;

class Chunk : public Entity
{
    public:
        Chunk( int x, int z,
               const Texture_Atlas& atlas  );

        void generateMesh ();

        const Block::Block_Base& getBlock ( int x, int y, int z ) const;

        const Model& getModel () const;

    private:
        void makeBlock ( GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );

        void makeBack   (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeTop    (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeLeft   (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeRight  (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeFront  (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeBottom (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );

    private:
        std::map<Vector2i, Chunk_Ptr>* m_p_chunkMap;
        std::vector<Block::Block_Base*> m_blocks;

        Model    m_model;

        const Texture_Atlas* m_p_atlas;

        bool m_hasBlockData     = false;
        bool m_hasVertexData    = false;

        std::vector<GLfloat> m_vertexCoords;
        std::vector<GLfloat> m_textureCoords;

    public:
        static constexpr int WIDTH  = 10,
                             HEIGHT = 10;
};


#endif // CHUNK_H

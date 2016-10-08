#ifndef CHUNK_H
#define CHUNK_H

#include <unordered_map>
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
        Chunk( std::unordered_map<Vector2i, Chunk_Ptr>* chunkMap,
               const Vector2i& location,
               const Texture_Atlas& atlas  );

        void generateMesh ();

        const Block::Block_Base& getBlock ( int x, int y, int z ) const;

        const Model& getModel () const;

        const Vector2i m_location;

        bool hasVertexData () const;

    private:
        void makeBlock ( GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );

        void makeBack   (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeTop    (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeLeft   (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeRight  (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeFront  (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );
        void makeBottom (   GLfloat x, GLfloat y, GLfloat z, const Block::Block_Base& block );

    private:
        std::unordered_map<Vector2i, Chunk_Ptr>* m_p_chunkMap;
        std::vector<Block::Block_Base*> m_blocks;

        Model    m_model;

        const Texture_Atlas* m_p_atlas;

        bool m_hasBlockData     = false;
        bool m_hasVertexData    = false;

        std::vector<GLfloat> m_vertexCoords;
        std::vector<GLfloat> m_textureCoords;

    public:
        static constexpr int WIDTH  = 16,
                             HEIGHT = 128;

        static int maxHeight;
        static int minHeight;
};


#endif // CHUNK_H

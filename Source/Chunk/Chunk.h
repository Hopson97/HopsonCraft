#ifndef CHUNK_H
#define CHUNK_H

#include <vector>

#include "OpenGL/GLEW/glew.h"
#include "Utilities/Loader.h"

#include "Generations/Height_Generator.h"

#include "Blocks/Blocks.h"

class Block;

class Chunk
{
    public:
        Chunk   ( Loader& loader, int x, int z );
        ~Chunk  ();

        void reset( Loader& loader );

        Block& getBlock( int x, int y, int z );

        constexpr static int HEIGHT = 256;//128
        constexpr static int WIDTH  = 16;//16

        static int highestBlock;

        MeshPtr tempMesh;

    private:
        void makeBlock ( GLfloat x, GLfloat y, GLfloat z, const Block& block );

        void makeBack   (   GLfloat x, GLfloat y, GLfloat z, const Block& block );
        void makeTop    (   GLfloat x, GLfloat y, GLfloat z, const Block& block );
        void makeLeft   (   GLfloat x, GLfloat y, GLfloat z, const Block& block );
        void makeRight  (   GLfloat x, GLfloat y, GLfloat z, const Block& block );
        void makeFront  (   GLfloat x, GLfloat y, GLfloat z, const Block& block );
        void makeBottom (   GLfloat x, GLfloat y, GLfloat z, const Block& block );

        void addIndex();


        int m_xPos;
        int m_zPos;

        std::vector<Block*> m_blocks;

        std::vector<GLfloat>    m_vertexList;
        std::vector<GLfloat>    m_textureList;
        std::vector<GLuint>    m_indexList;
};

#endif // CHUNK_H

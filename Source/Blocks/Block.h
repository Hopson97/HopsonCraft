#ifndef BLOCK_H
#define BLOCK_H

#include "OpenGL/GLEW/glew.h"
#include <vector>

enum class Block_Type
{
    Air,
    Grass,
    Dirt,
    Stone
};

class Block
{
    public:
        Block( Block_Type type );

        virtual ~Block() { }

        const Block_Type type;

        virtual std::vector<GLfloat> getSideTxrCoords   () const { return { 0 }; }
        virtual std::vector<GLfloat> getTopTxrCoords    () const { return { 0 }; }
        virtual std::vector<GLfloat> getBottomTxrCoords () const { return { 0 }; }

};

#endif // BLOCK_H

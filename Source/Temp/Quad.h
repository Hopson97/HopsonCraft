#ifndef QUAD_H_INCLUDED
#define QUAD_H_INCLUDED

#include "../Entity.h"
#include "../Model.h"

namespace Texture
{
    class Atlas;
}

class Quad : public Entity
{
    public:
        Quad(Texture::Atlas& textureAtlas);

        const Model& getModel() const;

    private:
        Model m_model;
};

#endif // QUAD_H_INCLUDED

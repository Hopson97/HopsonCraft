#ifndef CHUNK_H
#define CHUNK_H

#include "Block.h"
#include "Chunk_Layer.h"
#include "Chunk_Mesh.h"

#include <vector>
#include <unordered_map>

class Texture_Atlas;

class Chunk
{
    public:
        Chunk(const Texture_Atlas& blockAtlas);

        const Block::Block_Base& getBlock(int x, int y, int z) const;

        const Texture_Atlas& getAtlas () const;

        void setBlockData ();
        void bufferMesh   ();

        void bind();
        void draw();

    private://Functions
        void addLayer();

    private:
        const Texture_Atlas* m_p_atlas;

        std::vector<Chunk_Layer> m_layers; //Like an onion

        Chunk_Mesh m_mesh;

    public:
        constexpr static auto SIZE = 25; //The Width/ Depth of a single chunk
};

#endif // CHUNK_H

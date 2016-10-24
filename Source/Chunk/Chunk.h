#ifndef CHUNK_H
#define CHUNK_H

#include "Block.h"
#include "Chunk_Layer.h"
#include "Chunk_Mesh.h"
#include "Chunk_Position.h"

#include <vector>
#include <unordered_map>

class Texture_Atlas;
class Chunk_Map;

class Chunk
{
    public:
        Chunk(const Chunk_Position& position, Chunk_Map& chunkMap, const Texture_Atlas& blockAtlas);

        const Block::Block_Base& getBlock(int x, int y, int z) const;

        const Texture_Atlas& getAtlas () const;

        const Chunk_Mesh& getMesh () const;

        void generateMesh ();
        void bufferMesh   ();

        const Vector3& getGlPosition() const;

    private://Functions
        void addLayer();
        void setBlockData ();

    private:
        const Chunk_Position    m_location;
        const Vector3           m_glPosition;

        Chunk_Map*              m_p_chunkMap;
        const Texture_Atlas*    m_p_atlas;

        std::vector<Chunk_Layer> m_layers; //Like an onion

        Chunk_Mesh m_mesh;

    public:
        constexpr static auto SIZE = 25; //The Width/ Depth of a single chunk
};

#endif // CHUNK_H

#include "Position_Converter_Maths.h"

#include <cmath>

#include "../World/Chunk/Chunk.h"
#include "../World/World_Constants.h"

namespace Maths
{
    Block_Location worldToBlockPosition(const Vector3& worldPosition)
    {
        int x = (int) worldPosition.x % World::CHUNK_SIZE;
        int z = (int) worldPosition.z % World::CHUNK_SIZE;

        return  {x, (int)worldPosition.y, z};
    }



    Chunk_Location worldToChunkPosition(const Vector3& worldPosition)
    {
        return  {(int)std::floor( worldPosition.x / World::CHUNK_SIZE),
                 (int)std::floor( worldPosition.z / World::CHUNK_SIZE)};
    }

    unsigned getChunkDistance(const Chunk_Location& l1, const Chunk_Location& l2)
    {
        auto dx = std::abs(l1.x - l2.x);
        auto dz = std::abs(l1.z - l2.z);

        return std::sqrt(dx * dx + dz * dz );
    }

    Vector3 chunkBlockToWorldCoords(const Block_Location& bLocation,
                                    const Chunk_Location& cLocation)
    {
        int x = cLocation.x * World::CHUNK_SIZE;
        int z = cLocation.z * World::CHUNK_SIZE;

        x += bLocation.x;
        z += bLocation.z;
        int y = bLocation.y;

        return {x, y, z};
    }


}

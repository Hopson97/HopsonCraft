#include "Position_Converter_Maths.h"

#include <cmath>

#include "Chunk/Chunk.h"

namespace Maths
{
    Vector3 worldToBlockPosition(const Vector3& worldPosition)
    {
        int x;
        int z;

        if ( worldPosition.x < 0 )
        {
            x = abs( Chunk::SIZE + (int) std::floor(worldPosition.x) % Chunk::SIZE );
        }
        else
        {
            x = (int) worldPosition.x % Chunk::SIZE;
        }

        if ( worldPosition.z < 0 )
        {
            z = abs(Chunk::SIZE + (int) std::floor(worldPosition.z) % Chunk::SIZE);
        }
        else
        {
            z = (int) worldPosition.z % Chunk::SIZE;
        }
        return  {x, (int)worldPosition.y, z};
    }



    Chunk_Location worldToChunkPosition(const Vector3& worldPosition)
    {
        return  {(int)std::floor( worldPosition.x / Chunk::SIZE),
                 (int)std::floor( worldPosition.z / Chunk::SIZE)};
    }

    unsigned getChunkDistance(const Chunk_Location& l1, const Chunk_Location& l2)
    {
        auto dx = std::abs(l1.x - l2.x);
        auto dz = std::abs(l1.z - l2.z);

        return std::sqrt(dx * dx + dz * dz );
    }

    Vector3 chunkBlockToWolrdCoords(const Vector3& blocks, const Chunk_Location& location)
    {
        //int x;
        //int y;
        //int z;

        //int cx = location.x * Chunk::SIZE;
        //int cz = location.z * Chunk::SIZE;
    }

}

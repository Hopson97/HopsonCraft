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
}

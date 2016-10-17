#include "Maths.h"

#include <iostream>

#include "Camera.h"
#include "Chunk/Chunk.h"

namespace Maths
{
    Matrix4 createViewMatrix ( const Camera& camera )
    {
        Matrix4 view;

        view = glm::rotate     ( view, glm::radians( camera.getRotation().x ), { 1, 0, 0} );
        view = glm::rotate     ( view, glm::radians( camera.getRotation().y ), { 0, 1, 0} );
        view = glm::translate  ( view, -camera.getPosition() );

        return view;
    }

    Matrix4 createTransforrmationMatrix( const Vector3& translation,
                                         const Vector3& rotation,
                                         const Vector3& scale )
    {
        Matrix4 transformation;

        transformation = glm::translate( transformation, translation );

        transformation = glm::rotate( transformation, glm::radians( rotation.x ), { 1, 0, 0 } );
        transformation = glm::rotate( transformation, glm::radians( rotation.y ), { 0, 1, 0 } );
        transformation = glm::rotate( transformation, glm::radians( rotation.z ), { 0, 0, 1 } );

        transformation = glm::scale( transformation, scale );

        return transformation;
    }

    Vector2i worldToChunkLocation   ( const Vector3& worldPos )
    {
        return  {   (int)std::floor( worldPos.x / Chunk::WIDTH ),
                    (int)std::floor( worldPos.z / Chunk::WIDTH )
                };
    }

    Vector3 worldToBlockInChunkPos ( const Vector3& worldPos )
    {
        int x;
        int z;

        if ( worldPos.x < 0 )
        {
            x = abs( Chunk::WIDTH + (int) std::floor( worldPos.x ) % Chunk::WIDTH );
        }
        else
        {
            x = (int) worldPos.x % Chunk::WIDTH;
        }

        if ( worldPos.z < 0 )
        {
            z = abs( Chunk::WIDTH + (int) std::floor( worldPos.z ) % Chunk::WIDTH );
        }
        else
        {
            z = (int) worldPos.z % Chunk::WIDTH;
        }
        return  {   x,
                    (int) worldPos.y,
                    z
                };
    }
}

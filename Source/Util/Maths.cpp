#include "Maths.h"

#include "Camera.h"

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
}

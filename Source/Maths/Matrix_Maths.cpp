#include "Matrix_Maths.h"

#include "../Entity.h"
#include "../Util/Display.h"
#include "../Play_Settings.h"

#include "../Entity.h"
#include "../Camera.h"

namespace Maths
{
    Matrix4 createViewMatrix (const Camera& camera)
    {
        Matrix4  viewMatrix;
        viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.rotation.x), {1, 0, 0});
        viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.rotation.y), {0, 1, 0});
        viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.rotation.z), {0, 0, 1});

        return glm::translate(viewMatrix, -camera.position);
    }

    Matrix4 createViewRotationMatrix(const Camera& camera)
    {
        Matrix4  viewMatrix;
        viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.rotation.x), {1, 0, 0});
        viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.rotation.y), {0, 1, 0});
        return       glm::rotate(viewMatrix, glm::radians(camera.rotation.z), {0, 0, 1});
    }

    Matrix4 createViewTranslationMatrix(const Camera& camera)
    {
        Matrix4  viewMatrix;
        return glm::translate(Matrix4(), -camera.position);
    }

    Matrix4 createModelMatrix(const Entity& entity)
    {
        Matrix4 transform;



        transform = glm::rotate(transform, glm::radians(entity.rotation.x), {1, 0, 0});
        transform = glm::rotate(transform, glm::radians(entity.rotation.y), {0, 1, 0});
        transform = glm::rotate(transform, glm::radians(entity.rotation.z), {1, 0, 1});

        transform = glm::translate(transform, entity.position);

        return glm::scale(transform, entity.scale);
    }

    Matrix4 createPerspectiveMatrix ()
    {
        return glm::perspective(glm::radians(Settings::getFOV()),
                                Display::getAspect(),
                                Settings::NEAR_PLANE,
                                Settings::FAR_PLANE);
    }
}

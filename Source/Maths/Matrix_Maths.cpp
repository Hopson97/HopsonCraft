#include "Matrix_Maths.h"

#include "../Entity/Entity.h"
#include "../Util/Display.h"
#include "../D_Settings.h"

#include "../Entity/Entity.h"

namespace Maths
{
    Matrix4 createViewMatrix (const Entity& camera)
    {
        Matrix4  viewMatrix;
        viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.rotation.x), {1, 0, 0});
        viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.rotation.y), {0, 1, 0});
        viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.rotation.z), {0, 0, 1});

        return glm::translate(viewMatrix, -camera.position);
    }

    Matrix4 createModelMatrix(const Entity& entity)
    {
        Matrix4 transform;

        transform = glm::translate(transform, entity.position);

        transform = glm::rotate(transform, glm::radians(entity.rotation.x), {1, 0, 0});
        transform = glm::rotate(transform, glm::radians(entity.rotation.y), {0, 1, 0});
        transform = glm::rotate(transform, glm::radians(entity.rotation.z), {1, 0, 1});

        return glm::scale(transform, entity.scale);
    }

    Matrix4 createPerspectiveMatrix ()
    {
        return glm::perspective(glm::radians(Settings::FOV),
                                Display::getAspect(),
                                Settings::NEAR_PLANE,
                                Settings::FAR_PLANE);
    }
}

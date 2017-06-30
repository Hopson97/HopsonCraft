#include "Matrix.h"

#include "../Entity/Entity.h"
#include "../Display.h"

#include "../Camera.h"

namespace Maths
{
    Matrix4 createViewMatrix(const Camera& camera) noexcept
    {
        Matrix4 matrix;

        matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), {1, 0, 0});
        matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), {0, 1, 0});
        matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), {0, 0, 1});

        matrix = glm::translate(matrix, -camera.position);

        return matrix;
    }

    Matrix4 createModelMatrix(const Entity& entity) noexcept
    {
        Matrix4 matrix;

        matrix = glm::translate(matrix, entity.position);

        matrix = glm::rotate(matrix, glm::radians(entity.rotation.x), {1, 0, 0});
        matrix = glm::rotate(matrix, glm::radians(entity.rotation.y), {0, 1, 0});
        matrix = glm::rotate(matrix, glm::radians(entity.rotation.z), {0, 0, 1});

        return matrix;
    }

    Matrix4 createProjMatrix(float fieldOfView) noexcept
    {
        return glm::perspective(glm::radians(fieldOfView),
                                (float)getDisplay().get().getSize().x/ (float)getDisplay().get().getSize().y,
                                0.1f,
                                1000.0f);
    }
}

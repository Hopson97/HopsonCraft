#include "Camera.h"

#include <cmath>
#include <iostream>

#include "Maths/Matrix_Maths.h"

Camera::Camera()
{
    m_projectionMatrix = Maths::createProjMatrix();
}

void Camera::update()
{
    position = m_P_entity->position;
    rotation = m_P_entity->rotation;

    m_viewMatrix = Maths::createViewMatrix(*this);
    m_frustum.update(m_projectionMatrix * m_viewMatrix);
}

void Camera::hookEntity(const Entity& entity)
{
    m_P_entity = &entity;
    update();
}

const Frustum& Camera::getFrustum() const
{
    return m_frustum;
}


const Matrix4& Camera::getViewMatrix() const
{
    return m_viewMatrix;
}

const Matrix4& Camera::getProjectionMatrix() const
{
    return m_projectionMatrix;
}





































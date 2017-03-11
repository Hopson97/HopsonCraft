#include "Camera.h"

#include <cmath>
#include <iostream>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Display.h"
#include "Input/Key_Binds.h"
#include "Input/Function_Toggle_Key.h"


Camera::Camera()
{
    rotation.y += 180;
}


void Camera::update()
{
    position = m_P_entity->position;
    rotation = m_P_entity->rotation;
}

void Camera::hookEntity(const Entity& entity)
{
    m_P_entity = &entity;
}















































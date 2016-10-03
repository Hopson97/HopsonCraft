#version 330 core

layout (location = 0)   in vec3 vertexPosition;
layout (location = 1)   in vec2 textures;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 txrCoords;


void main()
{

    txrCoords = textures;
    vec4 worldPosition = modelMatrix * vec4 ( vertexPosition, 1.0f );

    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}

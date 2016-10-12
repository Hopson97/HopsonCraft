#version 330 core

layout ( location = 0 ) in vec3 vertexPosition;
layout ( location = 1 ) in vec2 texturePosition;

out vec2 textureCoords;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

uniform float time;

void main()
{
    textureCoords = texturePosition;

    vec4 worldPosition = modelMatrix * vec4 ( vertexPosition, 1.0f );

    gl_Position = projectionMatrix * viewMatrix * worldPosition;

    gl_Position.y -= 0.25;

    gl_Position.y += sin( time ) / 8;
}

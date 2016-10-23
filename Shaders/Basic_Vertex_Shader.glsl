#version 330 core

layout (location = 0) in vec3 inVertexCoords;
layout (location = 1) in vec2 inTextureCoords;

out vec2 passTextureCoords;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec4 worldPosition          = modelMatrix * vec4 (inVertexCoords, 1.0f);
    vec4 posRelativeToCamera    = viewMatrix * worldPosition;
    gl_Position                 = projectionMatrix * posRelativeToCamera;

    passTextureCoords = inTextureCoords;
}

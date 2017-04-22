#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTextureCoords;

out vec2 passTextureCoords;

uniform mat4 modelMatrix;
uniform mat4 projViewMatrix;

void main()
{
    gl_Position = projViewMatrix * modelMatrix *
                  vec4 (inVertexPosition.x,
                        inVertexPosition.y,
                        inVertexPosition.z,
                        1.0);

    passTextureCoords = inTextureCoords;
}

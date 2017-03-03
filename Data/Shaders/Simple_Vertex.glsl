#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTextureCoords;

out vec2 passTextureCoords;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projMatrix;

void main()
{
    gl_Position = projMatrix * viewMatrix * modelMatrix *
                  vec4 (inVertexPosition.x,
                        inVertexPosition.y,
                        inVertexPosition.z,
                        1.0);

    passTextureCoords = inTextureCoords;
}

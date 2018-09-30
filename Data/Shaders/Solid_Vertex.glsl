#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTextureCoords;
layout (location = 2) in vec3 inLightValue;

out vec2 passTextureCoords;
out vec3 passLightValue;

out float passTimer;


uniform mat4 projViewMatrix;
uniform float timer;

void main()
{
    gl_Position = projViewMatrix * vec4(inVertexPosition, 1.0);

    passTextureCoords = inTextureCoords;
    passLightValue = inLightValue;

    passTimer = abs(sin(timer / 10));
}

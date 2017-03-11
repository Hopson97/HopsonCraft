#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTextureCoords;
layout (location = 2) in float inLightValue;

out vec2 passTextureCoords;
out float passLightValue;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projMatrix;

void logFarNearPlane(float near, float far)
{
    gl_Position.z = 2.0 * log(gl_Position.w / near) / log(far / near) - 1;
    gl_Position.z *= gl_Position.w;
}

void main()
{
    gl_Position =   projMatrix * viewMatrix * modelMatrix * vec4 (inVertexPosition.xyz, 1.0);

    //logFarNearPlane(0.1, 1000.0f);

    passTextureCoords = inTextureCoords;
    passLightValue    = inLightValue;
}

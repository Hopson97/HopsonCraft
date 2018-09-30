#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTextureCoords;
layout (location = 2) in vec3 inLightValue;

out vec2 passTextureCoords;
out vec3 passLightValue;

out float passTimer;

uniform mat4 projViewMatrix;
uniform float timer;

vec4 getWorldPos()
{
    vec3 inVert = inVertexPosition.xyz;
    inVert.x += sin((timer + inVert.z + inVert.y) * 1.8f) / 15.0f;
    inVert.z -= cos((timer + inVert.x + inVert.y) * 1.8f) / 15.0f;
    return vec4(inVert, 1);
}

void main()
{
    gl_Position = projViewMatrix * getWorldPos();

    passTextureCoords = inTextureCoords;
    passLightValue    = inLightValue;

    passTimer = abs(sin(timer / 10));
}

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
    inVert.y += sin((timer + inVert.x) * 1.5) / 8.8f;
    inVert.y += cos((timer + inVert.z) * 1.5) / 8.1f;
    inVert.y -= 0.2;
    return vec4(inVert, 1);
}

void main()
{
    gl_Position = projViewMatrix * getWorldPos();

    passTextureCoords = inTextureCoords;
    passLightValue    = inLightValue;

    passTimer = abs(sin(timer / 10));
}

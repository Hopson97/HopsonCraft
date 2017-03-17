#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTextureCoords;
layout (location = 2) in float inLightValue;

out vec2 passTextureCoords;
out float passLightValue;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform float waveTimer;

vec4 getWorldPos()
{
    vec3 inVert = inVertexPosition.xyz;
    inVert.y -= 0.23f;
    inVert.y += sin((waveTimer + inVert.z) * 2.5) / 8.8f;
    inVert.y += cos((waveTimer + inVert.x) * 2.5) / 8.8f;
    return vec4(inVert, 1);
}

void main()
{
    vec4 worldPos = getWorldPos();
    gl_Position =   projMatrix * viewMatrix * worldPos;

    passTextureCoords = inTextureCoords;
    passLightValue    = inLightValue;
}

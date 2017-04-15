#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTextureCoords;
layout (location = 2) in float inLightValue;

out vec2 passTextureCoords;
out float passLightValue;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform float windTimer;

vec4 getWorldPos()
{
    vec3 inVert = inVertexPosition.xyz;
    inVert.x += sin((windTimer + inVert.z) * 2.5) / 8.8f;
    inVert.z += cos((windTimer + inVert.x) * 2.5) / 8.8f;
    return vec4(inVert, 1);
}

void main()
{
    gl_Position =   projMatrix * viewMatrix * getWorldPos();

    passTextureCoords = inTextureCoords;
    passLightValue    = inLightValue;
}

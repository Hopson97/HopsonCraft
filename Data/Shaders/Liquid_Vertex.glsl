#version 330

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTextureCoords;
layout (location = 2) in float inLightValue;

out vec2 passTextureCoords;
out float passLightValue;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projMatrix;

uniform float waveTimer;

void logFarNearPlane(float near, float far)
{
    gl_Position.z = 2.0 * log(gl_Position.w / near) / log(far / near) - 1;
    gl_Position.z *= gl_Position.w;
}

vec4 getWorldPos()
{
    vec4 worldPosition = modelMatrix * vec4(inVertexPosition, 1.0f);
    worldPosition.y -= 0.22;

    worldPosition.y += sin((waveTimer + worldPosition.z) * 2.5) / 8.8f;
    worldPosition.y += cos((waveTimer + worldPosition.x) * 2.5) / 8.8f;

    return worldPosition;
}

void main()
{
    vec4 worldPos = getWorldPos();

    gl_Position =   projMatrix * viewMatrix * worldPos;

    //logFarNearPlane(0.1, 1000.0f);

    passTextureCoords = inTextureCoords;
    passLightValue    = inLightValue;
}

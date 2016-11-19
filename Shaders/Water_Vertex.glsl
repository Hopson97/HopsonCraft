#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 texturePosition;

out vec2 passTextureCoords;
out float passVis;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform float time;

//Fog
const float density     = 0.0025;
const float gradient    = 5.00;

void calculateFog (vec4 vertRelToCamera)
{
    float dist = length (vertRelToCamera.xyz);
    passVis = exp       (-pow (dist * density , gradient));
    passVis = clamp     (passVis, 0.0, 1.0);
}

vec4 getWorldPosition()
{
    vec4 worldPosition = modelMatrix * vec4 ( vertexPosition, 1.0f );

    worldPosition.y -= 0.2;
    worldPosition.y += sin((time + worldPosition.z) * 2.5) / 8.8f;
    worldPosition.y += cos((time + worldPosition.x) * 2.5) / 8.8f;

    return worldPosition;
}

void main()
{
    vec4 worldPosition      =   getWorldPosition();
    vec4 vertRelToCamera    =   viewMatrix * worldPosition;

    gl_Position = projectionMatrix * vertRelToCamera;

    calculateFog( vertRelToCamera );
    passTextureCoords = texturePosition;
}

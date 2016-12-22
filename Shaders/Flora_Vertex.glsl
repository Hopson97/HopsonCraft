#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 texturePosition;
layout (location = 2) in float  inLightValue;

out vec2 passTextureCoords;
out float passVis;
out float passLightValue;


uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform float time;

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

    worldPosition.x += sin((time + worldPosition.z + worldPosition.y) * 1.8) / 15.0f;
    worldPosition.z -= cos((time + worldPosition.x + worldPosition.y) * 1.8) / 15.0f;

    return worldPosition;
}

void main()
{
    vec4 worldPosition      =   getWorldPosition();
    vec4 vertRelToCamera    =   viewMatrix * worldPosition;

    gl_Position = projectionMatrix * vertRelToCamera;

    calculateFog(vertRelToCamera);
    passTextureCoords = texturePosition;

    passLightValue = inLightValue;
}

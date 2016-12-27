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

const float density     = 0.0025;
const float gradient    = 5.00;

void calculateFog ( vec4 vertRelToCamera )
{
    float dist = length ( vertRelToCamera.xyz);
    passVis = exp       (-pow (dist * density , gradient));
    passVis = clamp     (passVis, 0.0, 1.0);
}

void main()
{
    vec4 worldPosition      = modelMatrix   * vec4 ( vertexPosition, 1.0f );
    vec4 vertRelToCamera    = viewMatrix    * worldPosition;

    gl_Position = projectionMatrix * vertRelToCamera;

    calculateFog( vertRelToCamera );

    passTextureCoords = texturePosition;

    passLightValue = inLightValue;
}

#version 330 core

layout ( location = 0 ) in vec3 vertexPosition;
layout ( location = 1 ) in vec2 texturePosition;

out vec2 textureCoords;

out float vis;


uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

uniform float time;

//Fog
const float density     = 0.0035;
const float gradient    = 2.82;

void calculateFog (vec4 vertRelToCamera)
{
    float dist = length ( vertRelToCamera.xyz );
    vis = exp( -pow ( dist * density , gradient ) );
    vis = clamp ( vis, 0.0, 1.0 );
}

vec4 makeWaves ( vec4 worldPos )
{
    worldPos.y -= 0.2;
    worldPos.y += sin((time + worldPos.z)) / 8.8f;
    worldPos.y += cos((time + worldPos.x)) / 8.8f;

    return worldPos;
}

void main()
{
    textureCoords = texturePosition;

    vec4 worldPosition = modelMatrix * vec4 ( vertexPosition, 1.0f );

    worldPosition = makeWaves ( worldPosition );

    vec4 vertRelToCamera = viewMatrix * worldPosition;
    gl_Position = projectionMatrix * vertRelToCamera;


    calculateFog( vertRelToCamera );

    //gl_Position.y -= (vertRelToCamera.z * vertRelToCamera.z) / 1000;
}

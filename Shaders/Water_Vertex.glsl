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
const float density     = 0.0034;
const float gradient    = 3.0;

void makeWaves ( vec4 worldPos )
{
    gl_Position.y -= 0.18;
    gl_Position.y += sin( time + worldPos.x * worldPos.z  ) /8.3;
}

void main()
{
    textureCoords = texturePosition;

    vec4 worldPosition = modelMatrix * vec4 ( vertexPosition, 1.0f );
    vec4 vertRelToCamera = viewMatrix * worldPosition;
    gl_Position = projectionMatrix * vertRelToCamera;

    makeWaves ( worldPosition );

    //Fog calculations
    float dist = length ( vertRelToCamera.xyz );
    vis = exp( -pow ( dist * density , gradient ) );
    vis = clamp ( vis, 0.0, 1.0 );
}

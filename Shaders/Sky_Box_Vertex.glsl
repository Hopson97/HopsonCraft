#version 330 core

layout (location = 0) in vec3 inVertexCoord;
layout (location = 1) in vec2 inTexCoord;

out vec2 passTextureCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
     gl_Position = projectionMatrix * viewMatrix * vec4(inVertexCoord, 1.0);
     passTextureCoords = inTexCoord;
}

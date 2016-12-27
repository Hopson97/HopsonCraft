#version 330 core

in vec3 passTextureCoords;

out vec4 outColour;

uniform samplerCube cubeMap;

void main()
{
     outColour = texture(cubeMap, passTextureCoords);
}

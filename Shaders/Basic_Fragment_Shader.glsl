#version 330 core

out vec4 outColour;

in vec2 passTextureCoords;

uniform sampler2D textureSampler;

void main()
{
    outColour = texture(textureSampler, passTextureCoords);
}

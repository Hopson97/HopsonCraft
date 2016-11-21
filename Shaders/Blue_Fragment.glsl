#version 330 core

in vec2 passTextureCoords;

out vec4 outColour;

uniform sampler2D screenTexture;

void main()
{
    outColour = texture(screenTexture, passTextureCoords);

    outColour.r = 0;
    outColour.g = 0;
}

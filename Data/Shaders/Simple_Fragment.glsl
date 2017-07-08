#version 330

out vec4 colour;

in vec2 passTextureCoords;

uniform sampler2D ourTexture;

void main()
{
    colour = texture(ourTexture, passTextureCoords);
}

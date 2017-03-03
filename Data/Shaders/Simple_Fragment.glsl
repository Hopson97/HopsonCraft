#version 330

out vec4 colour;

in vec2 passTextureCoords;

uniform sampler2D ourTexture;

uniform float time;

void main()
{
    colour = texture(ourTexture, passTextureCoords);// * sin(time);
}

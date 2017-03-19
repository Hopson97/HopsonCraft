#version 330

out vec4 colour;

in  vec2  passTextureCoords;
//in float passLightValue;

uniform sampler2D ourTexture;

void main()
{
    colour = texture(ourTexture, passTextureCoords);// * passLightValue;
}

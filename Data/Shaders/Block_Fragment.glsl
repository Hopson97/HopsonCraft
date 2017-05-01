#version 330

out vec4 colour;

in vec2 passTextureCoords;
in vec3 passLightValue;

uniform sampler2D ourTexture;
uniform int maxLightValue;

void main()
{
    colour = texture(ourTexture, passTextureCoords) * passLightValue.x / maxLightValue;
    if (colour.a == 0)
    {
        discard;
    }
}

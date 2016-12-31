#version 330 core

in vec2 passTextureCoords;
in float passVis;
in vec3 passLightValues;

out vec4 outColour;

uniform sampler2D textureSampler;
uniform vec3 skyColour;

float   cardinalLight;
float   naturalLight;
float   blockLight;

void getLightValues()
{
    cardinalLight = passLightValues.r;
    naturalLight  = passLightValues.g;
    blockLight    = passLightValues.b;
}

void main()
{
    getLightValues();

    outColour = texture(textureSampler, passTextureCoords);
    outColour *= vec4(cardinalLight, cardinalLight, cardinalLight, 1.0);

    if (outColour.a == 0)
    {
        discard;
    }
    outColour = mix (vec4 ( skyColour, 1.0), outColour, passVis);
}

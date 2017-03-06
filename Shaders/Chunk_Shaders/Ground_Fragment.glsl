#version 330 core

in vec2 passTextureCoords;
in float passVis;
in vec3 passLightValues;

out vec4 outColour;

uniform sampler2D textureSampler;
uniform vec3 skyColour;
uniform int maxLightValue;

void main()
{
    float cardinalLight = passLightValues.r;
    float naturalLight  = passLightValues.g / maxLightValue;
    float blockLight    = passLightValues.b / maxLightValue;

    naturalLight = max(0.1, naturalLight);
    blockLight = max(0.1, blockLight);

    outColour = texture(textureSampler, passTextureCoords);
    outColour *= vec4(cardinalLight, cardinalLight, cardinalLight, 1.0);

    if(naturalLight > blockLight)
    {
        outColour *= vec4(naturalLight, naturalLight, naturalLight, 1.0);
    }
    else
    {
        outColour *= vec4(blockLight, blockLight, blockLight, 1.0);
    }

    if (outColour.a == 0)
    {
        discard;
    }
    outColour = mix (vec4 ( skyColour, 1.0), outColour, passVis);
}

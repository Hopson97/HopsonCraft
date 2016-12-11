#version 330 core

in vec2 passTextureCoords;
in float passVis;
in float passLightValue;

out vec4 outColour;

uniform sampler2D textureSampler;
uniform vec3 skyColour;

void main()
{
    outColour = texture(textureSampler, passTextureCoords);
    outColour *= vec4(passLightValue, passLightValue, passLightValue, 1.0);

    if (outColour.a == 0)
    {
        discard;
    }
    //outColour = mix (vec4 ( skyColour, 1.0), outColour, passVis);
}

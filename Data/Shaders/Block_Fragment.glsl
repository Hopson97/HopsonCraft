#version 330

out vec4 colour;

in vec2 passTextureCoords;
in vec3 passLightValue;

uniform sampler2D ourTexture;
uniform int maxLightValue;

void main()
{
    float cardinalLight = passLightValue.x / maxLightValue;
    float naturalLight  = passLightValue.y;
    float blockLight    = passLightValue.z;

    //Check if natural or block light is greater, as it will user the greater value
    float lightMultiplier = max(naturalLight, blockLight) / maxLightValue;

    //Add texture to the colour
    colour = texture(ourTexture, passTextureCoords);

    //Light multiplier
    colour *= cardinalLight * lightMultiplier;

    if (colour.a == 0)
    {
        discard;
    }
}

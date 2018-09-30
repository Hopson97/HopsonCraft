#version 330

out vec4 colour;

in vec2 passTextureCoords;
in vec3 passLightValue;

in float passTimer;

uniform sampler2D ourTexture;
uniform int maxLightValue;


void main()
{
    float timeOfDayVal = abs(sin(passTimer / 10));

    float cardinalLight = passLightValue.x / maxLightValue;
    float naturalLight  = passLightValue.y;// * passTimer;
    float blockLight    = passLightValue.z;


    naturalLight = max (naturalLight,   1.5f);
    blockLight   = max (blockLight,     1.5f);

    float lightVal = max(naturalLight, blockLight) / maxLightValue;

    //Check if natural or block light is greater, as it will user the greater value
    vec4 lightMultiplier = vec4(lightVal, lightVal, lightVal, 1.0f);

    //Add texture to the colour
    colour = texture(ourTexture, passTextureCoords);

    //Light multiplier
    colour *= cardinalLight;
    colour *= lightMultiplier;

    if (colour.a == 0)
    {
        discard;
    }
}

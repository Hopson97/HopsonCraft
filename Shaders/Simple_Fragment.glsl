#version 330 core

in vec2 passTextureCoords;

out vec4 outColour;

uniform sampler2D screenTexture;

const float offset = 1.0 / 300;

vec2 offsets[9] = vec2[]
(
    vec2(-offset, offset),  // top-left
    vec2(0.0f,    offset),  // top-center
    vec2(offset,  offset),  // top-right
    vec2(-offset, 0.0f),    // center-left
    vec2(0.0f,    0.0f),    // center-center
    vec2(offset,  0.0f),    // center-right
    vec2(-offset, -offset), // bottom-left
    vec2(0.0f,    -offset), // bottom-center
    vec2(offset,  -offset)  // bottom-right
);

float blurKernal[9] = float[]
(
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16
);

float sharpenKernal[9] = float[](
    -1, -1, -1,
    -1,  9, -1,
    -1, -1, -1
);

void main()
{
    outColour = texture(screenTexture, passTextureCoords);
    /*
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, passTextureCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * blurKernal[i];

    outColour = vec4(col, 1.0);

    outColour.g /= 3;
    outColour.r /= 3;
    */
}

#version 330 core

out vec4 color;

in vec2 passTextureCoords;

in float passVis;

uniform sampler2D   textureSampler;
uniform vec3        skyColour;

void main()
{
    color = texture(textureSampler, passTextureCoords);
    if ( color.a == 0 )
    {
        discard;
    }
    //color = mix ( vec4 ( skyColour, 1.0), color, passVis );
}

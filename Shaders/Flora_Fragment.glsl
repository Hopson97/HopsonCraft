#version 330 core

out vec4 color;

in vec2 textureCoords;

in float vis;

uniform sampler2D   textureSampler;
uniform vec3        skyColour;

void main()
{
    color = texture(textureSampler, textureCoords);
    if ( color.a == 0 )
    {
        discard;
    }

    //color.b = 0;
    //color.g = 0;
    color = mix ( vec4 ( skyColour, 1.0), color, vis );

}

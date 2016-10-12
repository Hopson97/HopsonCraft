#version 330 core

out vec4 color;

in vec2 textureCoords;

uniform sampler2D textureSampler;

void main()
{

    color = texture(textureSampler, textureCoords);
    if ( color.a == 0 )
    {
            discard;
    }
}

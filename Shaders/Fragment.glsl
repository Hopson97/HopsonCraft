#version 330 core

out vec4 color;

in vec2 textureCoords;

uniform sampler2D textureSampler;

uniform int isActive;

void main()
{
    if ( isActive == 1 )
    {
        color = texture(textureSampler, textureCoords) * vec4 ( 0.5, 0.1, 0.1, 1.0 );
    }
    else
    {
        color = texture(textureSampler, textureCoords);
    }
}

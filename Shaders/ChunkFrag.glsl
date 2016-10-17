#version 330 core

out vec4 color;

in vec2 textureCoords;

in float vis;

uniform sampler2D   textureSampler;
uniform int         isLocation;
uniform vec3        skyColour;

void main()
{



    if ( isLocation == 1 )
    {
        color = texture(textureSampler, textureCoords) * vec4 ( 0.5, 0.5, 0.5, 1);
        if ( color.a == 0 )
        {
           // discard;
        }
    }
    else
    {
        color = texture(textureSampler, textureCoords);
        if ( color.a == 0 )
        {
            discard;
        }
    }

    color = mix ( vec4 ( skyColour, 1.0), color, vis );
}

#version 330 core

out vec4 color;

in vec2 txrCoords;

uniform sampler2D textureSampler;

uniform int fog;

in float zPos;

void main()
{
    float col = abs(zPos);
    col = col / 175;
    col = 1 - col;
    if ( fog == 1 ) {
        color = texture ( textureSampler, txrCoords ) * vec4 ( col, col, col, 1);
    } else {
        color = texture ( textureSampler, txrCoords );
    }



}

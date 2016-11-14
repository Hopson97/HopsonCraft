#version 330 core
layout (location = 0) in vec2 inVertexCoords;
layout (location = 1) in vec2 inTextureCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(inVertexCoords.x, inVertexCoords.y, 0.0f, 1.0f);
    TexCoords = inTextureCoords;
}

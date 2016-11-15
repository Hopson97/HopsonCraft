#version 330 core
layout (location = 0) in vec3 inVertexCoords;
layout (location = 1) in vec2 inTextureCoords;

out vec2 passTextureCoords;

void main()
{
    gl_Position = vec4(inVertexCoords, 1.0f);
    passTextureCoords = inTextureCoords;
}

#version 330 core

layout (location = 0) in vec3 inVertexCoords;

out vec3 passTexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    passTexCoords = inVertexCoords;
    gl_Position = projection * view * vec4(inVertexCoords, 1.0);
}

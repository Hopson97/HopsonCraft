#version 330 core
out vec4 outColour;

in vec3 passTexCoords;

uniform samplerCube skybox;

void main()
{
    outColour = vec4(1, 1, 0, 1);//texture(skybox, passTexCoords);
}

#version 330 core

in vec3 inPosition;

out vec3 colour;

void main() 
{
    gl_Position = vec4(inPosition, 1.0);
    colour = vec3(inPosition.x + 0.5, 1.0, inPosition.y + 0.5);
}

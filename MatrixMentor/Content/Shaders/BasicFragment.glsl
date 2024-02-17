#version 410 core

layout(location = 0) in vec3 colour;

out vec4 outColour;

void main() 
{
    outColour = vec4(colour, 1.0);
}

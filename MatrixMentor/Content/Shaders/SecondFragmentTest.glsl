#version 410 core

in vec4 colour;

layout(location = 0) out vec4 outColour;

void main() 
{
    outColour = vec4(1) - colour;
}

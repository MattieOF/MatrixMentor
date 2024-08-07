#version 410 core

in vec3 inPosition;
in vec2 inUV;

out vec2 passUV;

void main() 
{
    gl_Position = vec4(inPosition, 1.0);
    passUV = inUV; // Pass through UVs
}

#version 410 core

in vec3 inPosition;
in vec2 inUV;

out vec2 passUV;

uniform mat4 transformMatrix;

void main() 
{
    gl_Position = transformMatrix * vec4(inPosition, 1.0);
    passUV = inUV; // Pass through UVs
}

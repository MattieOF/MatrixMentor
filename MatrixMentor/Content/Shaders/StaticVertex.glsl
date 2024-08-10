#version 410 core

in vec3 inPosition;
in vec2 inUV;

out vec2 passUV;

uniform mat4 transformMatrix;
uniform mat4 projectionMatrix;

void main() 
{
    gl_Position = projectionMatrix * transformMatrix * vec4(inPosition, 1.0);
    passUV = inUV; // Pass through UVs
}

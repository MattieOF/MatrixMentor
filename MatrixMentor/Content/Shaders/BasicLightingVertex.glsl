#version 410 core

in vec3 inPosition;
in vec2 inUV;
in vec3 inNormal;

out vec2 passUV;
out vec3 surfaceNormal;
out vec3 lightDirection;

uniform mat4 transformMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

void main() 
{
    vec4 worldPosition = transformMatrix * vec4(inPosition, 1.0);

    surfaceNormal = (transformMatrix * vec4(inNormal, 0.0f)).xyz;
    lightDirection = lightPosition - worldPosition.xyz; 
    passUV = inUV; // Pass through UVs

    gl_Position = projectionMatrix * viewMatrix * worldPosition;
}

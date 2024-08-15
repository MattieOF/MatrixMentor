#version 410 core

in vec2 passUV;
in vec3 surfaceNormal;
in vec3 lightDirection;

out vec4 outColour;

uniform sampler2D textureSampler;
uniform vec3 lightColor;

void main()
{
    vec3 normal = normalize(surfaceNormal);
    vec3 lightDir = normalize(lightDirection);
    
    float intensity = dot(normal, lightDir); // -1 to 1
    float brightness = max(intensity, 0.0);
    vec3 diffuse = brightness * lightColor;

    outColour = vec4(diffuse, 1.0f) * texture(textureSampler, passUV);
}

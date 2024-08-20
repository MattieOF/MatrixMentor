#version 410 core

in vec2 passUV;
in vec3 surfaceNormal;
in vec3 lightDirection;
in vec3 cameraDirection;

out vec4 outColour;

uniform sampler2D textureSampler;
uniform vec3 lightColor;

uniform float shineDamper;
uniform float reflectivity;

void main()
{
    vec3 normal = normalize(surfaceNormal);
    vec3 lightDir = normalize(lightDirection);
    
    float intensity = dot(normal, lightDir); // -1 to 1
    float brightness = max(intensity, 0.0);
    vec3 diffuse = brightness * lightColor;

    vec3 viewDir = normalize(cameraDirection);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specularIntensity = dot(reflectDir, viewDir);
    specularIntensity = max(specularIntensity, 0.0);
    float damped = pow(specularIntensity, shineDamper);
    vec3 specular = damped * reflectivity * lightColor;

    outColour = vec4(diffuse, 1.0f) * texture(textureSampler, passUV) + vec4(specular, 1.0f);
}

#version 410 core

in vec2 passUV;

out vec4 outColour;

uniform sampler2D textureSampler;

void main()
{
    outColour = texture(textureSampler, passUV);
}

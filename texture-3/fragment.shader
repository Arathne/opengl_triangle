#version 330 core

in vec3 fragColor;
in vec2 texCoords;

out vec4 fragOutput;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    fragOutput = mix(texture(texture1, texCoords), texture(texture2, texCoords), 0.2);
}

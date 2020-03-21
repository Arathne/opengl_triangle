#version 330 core

in vec3 fragColor;
in vec2 fragTexture;

out vec4 fragOutput;

uniform sampler2D picture;

void main()
{
    fragOutput = texture( picture, fragTexture ) * vec4( fragColor, 1.0 );
}

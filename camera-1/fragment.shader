#version 330 core

in vec2 texCoords;
out vec4 fragOutput;

uniform sampler2D picture;

void main()
{
    fragOutput = texture( picture, texCoords )* vec4( 0.5, 0.8, 0, 1.0 );
}

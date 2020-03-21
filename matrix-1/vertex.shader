#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texture;

out vec3 fragColor;
out vec2 fragTexture;

uniform mat4 transform;

void main()
{
    gl_Position = vec4( position, 1.0 ) * transform;
    fragColor = color;
    fragTexture = texture;
}

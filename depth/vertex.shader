#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;

out vec3 fragColor;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    texCoords = texture;
    gl_Position = projection * view * model * vec4( position, 1.0 );
}

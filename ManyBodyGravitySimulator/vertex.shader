#version 330 core

layout (location = 0) in vec2 bodyPosition;

void main()
{
    gl_Position = vec4(bodyPosition.x, bodyPosition.y, 0, 1.0);
}
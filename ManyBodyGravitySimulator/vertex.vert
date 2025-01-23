#version 330 core

layout (location = 0) in vec2 bodyPosition;
uniform vec2 uniformBodyPosition;
uniform mat4 camera;
uniform mat4 projection;
uniform mat4 translation;

void main()
{   
    gl_PointSize = 10.0;
    gl_Position = translation*projection*camera*vec4(uniformBodyPosition.x, uniformBodyPosition.y, 0, 1.0);
}
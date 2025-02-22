#version 330 core

layout (location = 0) in vec2 bodyPosition;
uniform vec2 uniformBodyPosition;
uniform mat4 camera;
uniform mat4 projection;
uniform mat4 translation;
uniform float normalisedMass;

void main()
{   
    if(normalisedMass > 0.7){ gl_PointSize = 30.0;}
    else if(normalisedMass > 0.95){ gl_PointSize = 250.0;}
    else {gl_PointSize = 5.0;}
    gl_Position = translation*projection*camera*vec4(uniformBodyPosition.x, uniformBodyPosition.y, 0, 1.0);
}
#version 330 core
out vec4 FragColor;

in vec4 vColor;
in vec3 vPosition;

uniform float Time;

void main()
{
    FragColor = vColor;
}
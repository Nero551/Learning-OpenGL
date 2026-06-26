#version 330 core
out vec4 FragColor;
in vec4 vertexColor;

uniform float Time;

void main()
{
    FragColor = vertexColor;
}
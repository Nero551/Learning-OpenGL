#version 330 core

out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;

uniform vec4 ObjectColor;
uniform vec4 LightColor;

void main()
{
    FragColor = ObjectColor;
}
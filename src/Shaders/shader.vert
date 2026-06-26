#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;

out vec3 vPosition;
out vec4 vColor;

uniform float uTime;

void main()
{
    vColor = aColor;
    vPosition = aPosition;
    gl_Position = vec4(aPosition, 1);
}
#version 330 core
layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;

out vec4 vPosition;
out vec4 vColor;
out vec2 vUV;

uniform mat4 uTransform;
uniform float uTime;

void main()
{
    vColor = aColor;
    vPosition = aPosition * uTransform;
    vUV = aUV;
    gl_Position = vPosition;
}
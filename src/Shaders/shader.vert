#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;

out vec3 vPosition;
out vec4 vColor;
out vec2 vUV;

uniform float uTime;

void main()
{
    vColor = aColor;
    vPosition = aPosition;
    vUV = aUV;

    gl_Position = vec4(vPosition, 1.0);
}
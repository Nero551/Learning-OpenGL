#version 330 core
layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;

out vec4 vPosition;
out vec4 vColor;
out vec2 vUV;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform float uTime;

void main()
{
    vColor = aColor;
    vPosition = uProjection * uView * uModel* aPosition;
    vUV = aUV;
    gl_Position =  vPosition;
}
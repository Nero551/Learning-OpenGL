#version 330 core
out vec4 FragColor;

in vec4 vColor;
in vec3 vPosition;
in vec2 vUV;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform float uTime;

void main()
{
    FragColor = texture(uTexture0, vUV) * vColor;
}
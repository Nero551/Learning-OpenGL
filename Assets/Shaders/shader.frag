#version 330 core

out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;

uniform sampler2D rubyTexture;

void main()
{
    FragColor = vec4(0, vUV, 1) - texture(rubyTexture, vUV);
}
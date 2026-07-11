#version 330 core

out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;

uniform sampler2D rubyTexture;
uniform sampler2D skullTexture;

void main()
{
    FragColor = vColor + texture(skullTexture, vUV) + texture(rubyTexture, vUV);
}
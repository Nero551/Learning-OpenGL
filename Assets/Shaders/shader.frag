#version 330 core

out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;

uniform sampler2D rubyTexture;

void main()
{
    float dist = distance(vUV, vec2(0.5, 0.5));

    float factor = 0.9 - smoothstep(0, 0.95, dist);

    FragColor = vec4(vec3(factor), 1.0) + texture(rubyTexture, vUV);
}
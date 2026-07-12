#version 330 core

out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

uniform float Time;

struct light {
    vec3 Color;
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

uniform light Light;


void main()
{
    FragColor = vec4(Light.Color, 1);
}
#version 330 core

#include "LightingShader.frag"
//#include "Material.frag"

void main()
{
    vec3 Lighting = ApplyLighting();
    FragColor = vec4(Lighting, 1) * Material.Color;
}
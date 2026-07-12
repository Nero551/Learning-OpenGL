#version 330 core

out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 ViewPosition;

uniform float Time;

struct material {
    vec4 Color;
    vec3 Diffuse;
    vec3 Ambient;
    vec3 Specular;
    float Shininess;
};

uniform material Material;

vec3 ApplyLighting(){
    //Ambient Lighting
    vec3 ambient = Material.Ambient * LightColor;

    //Diffuse Lighting
    vec3 lightDir = normalize(LightPosition - vPosition.xyz);
    float diff = max(dot(vNormal, lightDir), 0.0);
    vec3 diffuse = diff * LightColor * Material.Diffuse;

    //Specular Lighting;
    vec3 viewDir = normalize(ViewPosition - vec3(vPosition.xyz));
    vec3 reflectDir = reflect(-lightDir, vNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Material.Shininess);
    vec3 specular = spec * LightColor * Material.Specular;

    vec3 result = ambient + diffuse + specular;
    return result;
}

void main()
{
    vec3 Lighting = ApplyLighting();
    FragColor = vec4(Lighting, 1) * Material.Color;
}
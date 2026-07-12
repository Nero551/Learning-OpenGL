#version 330 core

out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

uniform vec4 ObjectColor;
uniform vec4 LightColor;
uniform vec3 LightPosition;
uniform vec3 ViewPosition;

uniform float Time;

uniform float AmbientStrength;
uniform float DiffuseStrength;
uniform float SpecularStrength;
uniform float SpecularShininess;

vec4 ApplyLighting(){

    //Ambient Lighting
    vec4 ambient = AmbientStrength * LightColor;

    //Diffuse Lighting
    vec3 lightDir = normalize(LightPosition - vec3(vPosition.xyz));
    float diff = max(dot(vNormal, lightDir), 0.0) * DiffuseStrength;
    vec4 diffuse = diff * LightColor * DiffuseStrength;

    //Specular Lighting;
    vec3 viewDir = normalize(ViewPosition - vec3(vPosition.xyz));
    vec3 reflectDir = reflect(-lightDir, vNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), SpecularShininess);
    vec4 specular = spec * LightColor * SpecularStrength;


    vec4 result = (ambient + diffuse + specular);
    return result;
}

void main()
{
    vec4 Lighting = ApplyLighting();
    FragColor = Lighting * ObjectColor;
}
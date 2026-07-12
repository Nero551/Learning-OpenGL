#version 330 core

out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

uniform vec4 ObjectColor;
uniform vec4 LightColor;
uniform vec3 LightPosition;
uniform float Time;

uniform float AmbientStrength;
uniform float DiffuseStrength;

void main()
{
    //Diffuse Lighting
    vec3 norm = normalize(vNormal);
    vec3 lightVector = normalize(LightPosition - vec3(vPosition.xyz));
    float diffuse = max(dot(norm, lightVector), 0.0) * DiffuseStrength;



    vec4 result = AmbientStrength * diffuse * LightColor * ObjectColor;
    FragColor = result;
}
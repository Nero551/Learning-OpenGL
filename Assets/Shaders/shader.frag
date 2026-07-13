#version 330 core

out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

uniform vec3 ViewPosition;
uniform float Time;

struct light {
    vec3 Color;
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct material {
    vec4 Color;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    vec3 Emission;

    float Shininess;

    sampler2D DiffuseMap;
    sampler2D SpecularMap;
    sampler2D EmissionMap;
};

uniform material Material;
uniform light Light;

vec3 ApplyLighting(){
    vec3 diffuseMap = vec3(texture(Material.DiffuseMap, vUV));
    vec3 specularMap = vec3(texture(Material.SpecularMap, vUV));
    vec3 emissionMap = vec3(texture(Material.EmissionMap, vUV));

    //Ambient Lighting
    vec3 ambient = Light.Color * diffuseMap * Light.Ambient * Material.Ambient;

    //Diffuse Lighting
    vec3 lightDir = normalize(Light.Position - vPosition.xyz);
    float diff = max(dot(vNormal, lightDir), 0.0);
    vec3 diffuse = diff * Light.Color * diffuseMap * Light.Diffuse * Material.Diffuse;

    //Specular Lighting
    vec3 viewDir = normalize(ViewPosition - vec3(vPosition.xyz));
    vec3 reflectDir = reflect(-lightDir, vNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Material.Shininess);
    vec3 specular = spec * Light.Color * specularMap * Material.Specular * Light.Specular;

    //Emission
    vec3 emission = emissionMap * Material.Emission;

    vec3 result = ambient + diffuse + specular + emission;
    return result;
}

void main()
{
    vec3 Lighting = ApplyLighting();
    FragColor = vec4(Lighting, 1) * Material.Color;
}
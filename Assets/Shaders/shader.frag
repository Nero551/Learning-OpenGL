#version 330 core

out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

uniform vec3 ViewPosition;
uniform float Time;

struct light {
    int Type;
    vec3 Direction;
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

uniform sampler2D rubyTexture;

vec3 ApplyLighting(){
    vec3 diffuseMap = vec3(texture(Material.DiffuseMap, vUV));
    vec3 specularMap = vec3(texture(Material.SpecularMap, vUV));
    vec3 emissionMap = vec3(texture(Material.EmissionMap, vUV));

    //Ambient Lighting
    vec3 ambient = Light.Color * diffuseMap * Light.Ambient * Material.Ambient;

    vec3 diffuse;
    vec3 specular;

    if (Light.Type == 0){
        //Directional
        vec3 lightDir = normalize(-Light.Direction);
        float diff = max(dot(vNormal, lightDir), 0.0);
        diffuse = diff * Light.Color * diffuseMap * Light.Diffuse * Material.Diffuse;

        vec3 viewDir = normalize(ViewPosition - vec3(vPosition.xyz));
        vec3 reflectDir = reflect(-lightDir, vNormal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), Material.Shininess);
        specular = spec * Light.Color * specularMap * Material.Specular * Light.Specular;
    }

    //Emission
    vec3 emission = emissionMap * Material.Emission;

    vec3 result = ambient + diffuse + specular + emission;
    return result;
}

void main()
{
    vec3 Lighting = ApplyLighting();
    FragColor = vec4(Lighting, 1) * Material.Color + texture(rubyTexture, vUV);
}
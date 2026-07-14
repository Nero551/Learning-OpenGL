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

    float Intensity;
    float Constant;
    float Linear;
    float Quadratic;

    float InnerCutOff;
    float OuterCutOff;
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

void CalculateDirectionalLight(out vec3 lightDir, out float directionalIntensity){
    lightDir = normalize(-Light.Direction);
    directionalIntensity = Light.Intensity;
}

void CalculatePointLight(out float attenuation){
    float dist = length(Light.Position - vPosition.xyz);
    attenuation = (1.0 / (Light.Quadratic * (dist * dist) + Light.Linear * dist + Light.Constant)) * Light.Intensity;
}

void CalculateSpotLight(vec3 lightDir, out float cutOff, out float attenuation){
    float dist = length(Light.Position - vPosition.xyz);
    attenuation = (1.0 / (Light.Constant + Light.Linear * dist + Light.Quadratic * (dist * dist))) * Light.Intensity;

    vec3 spotDir = normalize(-Light.Direction);
    float cosTheta = dot(lightDir, spotDir);
    float epsilon = Light.InnerCutOff - Light.OuterCutOff;
    cutOff = clamp((cosTheta - Light.OuterCutOff) / epsilon, 0.0, 1) * Light.Intensity;
}


vec3 ApplyLighting(){
    vec3 diffuseMap = vec3(texture(Material.DiffuseMap, vUV));
    vec3 specularMap = vec3(texture(Material.SpecularMap, vUV));
    vec3 emissionMap = vec3(texture(Material.EmissionMap, vUV));

    vec3 lightDir = normalize(Light.Position - vPosition.xyz);
    float cutOff = 1;
    float attenuation = 1;
    float directionalIntensity = 1;

    if (Light.Type == 0){
        CalculateDirectionalLight(lightDir, directionalIntensity);

    } else if (Light.Type == 1){
        CalculatePointLight(attenuation);

    } else if (Light.Type == 2){
        CalculateSpotLight(lightDir, cutOff, attenuation);
    }

    //Ambient
    vec3 ambient = Light.Color * diffuseMap * Light.Ambient * Material.Ambient * directionalIntensity;

    //Diffuse
    float diff = max(dot(vNormal, lightDir), 0.0);
    vec3 diffuse = diff * Light.Color * diffuseMap * Light.Diffuse * Material.Diffuse * attenuation * cutOff * directionalIntensity;

    //Specular
    vec3 viewDir = normalize(ViewPosition - vec3(vPosition.xyz));
    vec3 reflectDir = reflect(-lightDir, vNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Material.Shininess);
    vec3 specular = spec * Light.Color * specularMap * Material.Specular * Light.Specular * attenuation * cutOff * directionalIntensity;

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
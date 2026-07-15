#version 330 core

out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

uniform vec3 ViewPosition;
uniform float Time;

struct Light {
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

const int NR_LIGHTS = 24;
uniform int MaxLights;
uniform Light Lights[NR_LIGHTS];

uniform material Material;

void CalculateDirectionalLight(Light light, out vec3 lightDir, out float directionalIntensity){
    lightDir = normalize(-light.Direction);
    directionalIntensity = light.Intensity;
}

void CalculatePointLight(Light light, out float attenuation){
    float dist = length(light.Position - vPosition.xyz);
    attenuation = (1.0 / (light.Quadratic * (dist * dist) + light.Linear * dist + light.Constant)) * light.Intensity;
}

void CalculateSpotLight(Light light, vec3 lightDir, out float cutOff, out float attenuation){
    float dist = length(light.Position - vPosition.xyz);
    attenuation = (1.0 / (light.Constant + light.Linear * dist + light.Quadratic * (dist * dist))) * light.Intensity;

    vec3 spotDir = normalize(-light.Direction);
    float cosTheta = dot(lightDir, spotDir);
    float epsilon = light.InnerCutOff - light.OuterCutOff;
    cutOff = clamp((cosTheta - light.OuterCutOff) / epsilon, 0.0, 1) * light.Intensity;
}

vec3 CalculateLight(Light light){
    vec3 diffuseMap = vec3(texture(Material.DiffuseMap, vUV));
    vec3 specularMap = vec3(texture(Material.SpecularMap, vUV));

    vec3 lightDir = normalize(light.Position - vPosition.xyz);
    float cutOff = 1;
    float attenuation = 1;
    float directionalIntensity = 1;

    if (light.Type == 0){
        CalculateDirectionalLight(light, lightDir, directionalIntensity);

    } else if (light.Type == 1){
        CalculatePointLight(light, attenuation);

    } else if (light.Type == 2){
        CalculateSpotLight(light, lightDir, cutOff, attenuation);
    }

    //Ambient
    vec3 ambient = light.Color * diffuseMap * light.Ambient * Material.Ambient * directionalIntensity;

    //Diffuse
    float diff = max(dot(vNormal, lightDir), 0.0);
    vec3 diffuse = diff * light.Color * diffuseMap * light.Diffuse * Material.Diffuse * attenuation * cutOff * directionalIntensity;

    //Specular
    vec3 viewDir = normalize(ViewPosition - vec3(vPosition.xyz));
    vec3 reflectDir = reflect(-lightDir, vNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Material.Shininess);
    vec3 specular = spec * light.Color * specularMap * Material.Specular * light.Specular * attenuation * cutOff * directionalIntensity;

    return ambient + diffuse + specular;
}

vec3 ApplyLighting(){
    vec3 result;

    for (int i = 0; i < MaxLights; i++){
        result += CalculateLight(Lights[i]);
    }

    //Emission
    vec3 emissionMap = vec3(texture(Material.EmissionMap, vUV));
    vec3 emission = emissionMap * Material.Emission;
    result += emission;
    return result;
}

void main()
{
    vec3 Lighting = ApplyLighting();
    FragColor = vec4(Lighting, 1) * Material.Color;
}
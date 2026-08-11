#version 330 core
out vec4 FragColor;

in vec2 vUV;
in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;
in vec4 vWorldPosition;

uniform vec3 VIEW_POSITION;
uniform float TIME;

struct Material {
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

uniform Material MATERIAL;


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

vec3 CalculateAmbient(Light light, float directionalIntensity){
    vec3 diffuseMap = vec3(texture(MATERIAL.DiffuseMap, vUV));
    vec3 ambient = light.Color * diffuseMap * light.Ambient * MATERIAL.Ambient * directionalIntensity;
    return ambient;
}

vec3 CalculateDiffuse(Light light, vec3 lightDir, float attenuation, float cutOff, float directionalIntensity){
    vec3 diffuseMap = vec3(texture(MATERIAL.DiffuseMap, vUV));
    float diff = max(dot(vNormal, lightDir), 0.0);
    vec3 diffuse = diff * light.Color * diffuseMap * light.Diffuse * MATERIAL.Diffuse * attenuation * cutOff * directionalIntensity;
    return diffuse;
}

vec3 CalculateSpecular(Light light, vec3 lightDir, float attenuation, float cutOff, float directionalIntensity){
    vec3 specularMap = vec3(texture(MATERIAL.SpecularMap, vUV));
    vec3 viewDir = normalize(VIEW_POSITION - vec3(vWorldPosition.xyz));
    vec3 reflectDir = reflect(-lightDir, vNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), MATERIAL.Shininess);
    vec3 specular = spec * light.Color * specularMap * MATERIAL.Specular * light.Specular * attenuation * cutOff * directionalIntensity;

    return specular;
}

vec3 CalculateEmission(){
    vec3 emissionMap = vec3(texture(MATERIAL.EmissionMap, vUV));
    vec3 emission = emissionMap * MATERIAL.Emission;
    return emission;
}



void CalculateDirectionalLight(Light light, out vec3 lightDir, out float directionalIntensity) {
    lightDir = normalize(-light.Direction);
    directionalIntensity = light.Intensity;
}

void CalculatePointLight(Light light, out float attenuation) {
    float dist = length(light.Position - vWorldPosition.xyz);
    attenuation = (1.0 / (light.Quadratic * (dist * dist) + light.Linear * dist + light.Constant)) * light.Intensity;
}

void CalculateSpotLight(Light light, vec3 lightDir, out float cutOff, out float attenuation) {
    float dist = length(light.Position - vWorldPosition.xyz);
    attenuation = (1.0 / (light.Constant + light.Linear * dist + light.Quadratic * (dist * dist))) * light.Intensity;

    vec3 spotDir = normalize(-light.Direction);
    float cosTheta = dot(lightDir, spotDir);
    float epsilon = light.InnerCutOff - light.OuterCutOff;
    cutOff = clamp((cosTheta - light.OuterCutOff) / epsilon, 0.0, 1) * light.Intensity;
}


const int NR_LIGHTS = 24;
uniform int MAX_LIGHTS;
uniform Light LIGHTS[NR_LIGHTS];

vec3 CalculateLight(Light light) {
    vec3 lightDir = normalize(light.Position - vWorldPosition.xyz);
    float cutOff = 1;
    float attenuation = 1;
    float directionalIntensity = 1;

    if (light.Type == 0) {
        CalculateDirectionalLight(light, lightDir, directionalIntensity);

    } else if (light.Type == 1) {
        CalculatePointLight(light, attenuation);

    } else if (light.Type == 2) {
        CalculateSpotLight(light, lightDir, cutOff, attenuation);
    }

    //Phong Lighting Model
    vec3 ambient = CalculateAmbient(light, directionalIntensity);
    vec3 diffuse = CalculateDiffuse(light, lightDir, attenuation, cutOff, directionalIntensity);
    vec3 specular = CalculateSpecular(light, lightDir, attenuation, cutOff, directionalIntensity);

    return ambient + diffuse + specular;
}

vec3 Lighting() {
    vec3 result = vec3(0.0);
    for (int i = 0; i < MAX_LIGHTS; i++) {
        result += CalculateLight(LIGHTS[i]);
    }

    //Emission
    result += emission;
    return result;
}


void main()
{

    FragColor = vec4(Lighting(), 1) * MATERIAL.Color;

}

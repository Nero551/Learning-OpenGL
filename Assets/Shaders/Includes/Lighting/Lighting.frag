#include "PhongModel.frag"
#include "LightCasters.frag"

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

    vec3 emission = CalculateEmission();

    result += emission;
    return result;
}

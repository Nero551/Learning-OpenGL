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

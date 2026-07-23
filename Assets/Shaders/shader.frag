#include "Includes/Lighting.frag"

void main()
{
    vec3 Lighting = Lighting();
    FragColor = vec4(Lighting, 1) * Material.Color;
}
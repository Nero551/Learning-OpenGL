#include "Includes/Lighting.frag"

void main()
{
    vec3 Lighting = Lighting();
    FragColor = vec4(1, 0, 1, 1) * sin(Time) * vWorldPosition * vec4(vNormal, 1);
}
#include "Includes/Lighting.frag"

void main()
{
    FragColor = vec4(Lighting(), 1) * Material.Color;

}
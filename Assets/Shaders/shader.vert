#include "Includes/Default/Default.vert"

void main() {
    DefaultVertex();
    vPosition.x += cos(Time) * vNormal.x * exp(vNormal.x);
    vPosition.y += dot(vNormal, vWorldPosition.xyz * sin(Time));
    gl_Position = vPosition;
}

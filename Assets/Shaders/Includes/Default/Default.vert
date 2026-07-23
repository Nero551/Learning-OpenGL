layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aNormal;

out vec4 vPosition;
out vec4 vWorldPosition;
out vec4 vColor;
out vec2 vUV;
out vec3 vNormal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

uniform vec3 ViewPosition;
uniform float Time;

void DefaultVertex()
{
    vNormal = normalize(NormalMatrix * aNormal);
    vColor = aColor;
    vPosition = ProjectionMatrix * ViewMatrix * ModelMatrix * aPosition;
    vWorldPosition = ModelMatrix * aPosition;
    vUV = aUV;
}
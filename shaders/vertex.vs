// Trivial MVP Vertex Shader
// =========================
// This shader applies the MVP to the given position attribute and simply passes
// through the color attribute.

#version 400 core

uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

out vec3 fPosition;
out vec3 fNormal;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vPosition, 1.0);
    fPosition = vec3(modelMatrix * vec4(vPosition, 1.0));
    fNormal = normalMatrix * vNormal;
}

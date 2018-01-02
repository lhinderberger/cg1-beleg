// Trivial MVP Vertex Shader
// =========================
// This shader applies the MVP to the given position attribute and simply passes
// through the color attribute.

#version 400 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec4 vPosition;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vPosition;
}

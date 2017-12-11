// Trivial MVP Vertex Shader
// =========================
// This shader applies the MVP to the given position attribute and simply passes
// through the color attribute.

#version 400 core

uniform mat4 mvp;

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
out vec4 color;

void main() {
    gl_Position = mvp * vPosition;
    color = vColor;
}

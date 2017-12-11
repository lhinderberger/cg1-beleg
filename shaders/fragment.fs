// Trivial Fragment Shader
// =======================
// This shader just passes through the given color value

#version 400 core

in vec4 color;
layout(location = 0) out vec4 fColor;

void main() {
    fColor = color;
}

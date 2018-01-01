#version 400 core

in vec4 color;
uniform bool lightingEnabled;
uniform vec3 lightColor;
layout(location = 0) out vec4 fColor;

void main() {
	if (lightingEnabled)
	    fColor = vec4(lightColor * color.rgb, color.a);
    else
		fColor = color;
}

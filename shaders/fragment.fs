#version 400 core

uniform bool lightingEnabled;
uniform vec3 lightColor;
uniform vec4 objectColor;

layout(location = 0) out vec4 fColor;

void main() {
	if (lightingEnabled)
	    fColor = vec4(lightColor * objectColor.rgb, objectColor.a);
    else
		fColor = objectColor;
}

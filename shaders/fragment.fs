#version 400 core

uniform bool lightingEnabled;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec4 objectColor;

layout(location = 0) out vec4 fColor;

in vec3 fPosition;
in vec3 fNormal;

void main() {
	if (lightingEnabled) {
	    vec3 normal = normalize(fNormal);
	    vec3 lightDirection = normalize(lightPosition - fPosition);
	    
	    vec3 ambient = 0.1 * lightColor;
	    vec3 diffuse = max(dot(normal, lightDirection), 0.0) * lightColor;
	    
	    fColor = vec4((ambient + diffuse) * objectColor.rgb, objectColor.a);
    }
    else
		fColor = objectColor;
}

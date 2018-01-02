#version 400 core

uniform vec3 cameraPosition;
uniform bool lightingEnabled;
uniform vec4 objectColor;

layout(location = 0) out vec4 fColor;

in vec3 fPosition;
in vec3 fNormal;

void main() {
	if (lightingEnabled) {
	    vec3 lightColor = vec3(1.0,1.0,1.0);
	    vec3 lightPosition = vec3(2.0,2.0,2.0);
	
	    vec3 normal = normalize(fNormal);
	    vec3 lightDirection = normalize(fPosition - cameraPosition);
	    
	    vec3 viewingDirection = normalize(cameraPosition - fPosition);
	    vec3 reflectionDirection = reflect(lightDirection, normal);
	    
	    float ambientStrength = 0.1;
	    float diffuseStrength = 0.7;
	    float specularShininess = 32;
	    float specularStrength = 0.5;
	    
	    vec3 ambient = ambientStrength * lightColor;
	    vec3 diffuse = diffuseStrength * max(dot(normal, -1.0 * lightDirection), 0.0) * lightColor;
	    vec3 specular = specularStrength * pow(max(dot(viewingDirection, reflectionDirection), 0.0), specularShininess) * lightColor;
	    
	    fColor = vec4((ambient + diffuse + specular) * objectColor.rgb, objectColor.a);
    }
    else
		fColor = objectColor;
}

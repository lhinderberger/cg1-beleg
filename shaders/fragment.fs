#version 400 core

struct Material {
    vec3 ambient, diffuse, specular;
    float shininess;
};

uniform Material material;

uniform vec3 cameraPosition;
uniform bool lightingEnabled;
uniform vec4 objectColor;

layout(location = 0) out vec4 fColor;

in vec3 fPosition;
in vec3 fNormal;

void main() {
	if (lightingEnabled) {
	    vec3 lightColor = vec3(1.0,1.0,1.0);
	    vec3 lightPosition = vec3(1.0,1.0,1.0);
	
	    vec3 normal = normalize(fNormal);
	    vec3 lightDirection = normalize(lightPosition - fPosition);
	    
	    vec3 viewingDirection = normalize(cameraPosition - fPosition);
	    vec3 reflectionDirection = reflect(-1.0 * lightDirection, normal);
	    
	    vec3 ambient = material.ambient * lightColor;
	    vec3 diffuse = material.diffuse * max(dot(normal, lightDirection), 0.0) * lightColor;
	    vec3 specular = material.specular * pow(max(dot(viewingDirection, reflectionDirection), 0.0), material.shininess) * lightColor;
	    
	    fColor = vec4((ambient + diffuse + specular) * objectColor.rgb, objectColor.a);
    }
    else
		fColor = objectColor;
}

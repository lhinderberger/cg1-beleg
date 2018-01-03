#version 400 core

struct DirectionalLight {
    vec3 direction;
    vec3 ambient, diffuse, specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient, diffuse, specular;
    float constantDecay, linearDecay, quadraticDecay;
};

struct Material {
    vec3 ambient, diffuse, specular;
    float shininess;
};

uniform DirectionalLight sun;
uniform Material material;
uniform PointLight pointLights[100];
uniform int nPointLights;

uniform vec3 cameraPosition;
uniform bool lightingEnabled;
uniform bool texturingEnabled;
uniform vec4 objectColor;

uniform sampler2D textureData;

layout(location = 0) out vec4 fColor;

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoord;

vec3 directionalPhong(DirectionalLight light, vec3 normal, vec3 viewingDirection) {
    vec3 lightDirection = normalize(-1.0f * light.direction);
    vec3 reflectionDirection = reflect(-1.0 * lightDirection, normal);
    
    vec3 ambient = material.ambient * light.ambient;
    vec3 diffuse = material.diffuse * max(dot(normal, lightDirection), 0.0) * light.diffuse;
    vec3 specular = material.specular * pow(max(dot(viewingDirection, reflectionDirection), 0.0), material.shininess) * light.specular;
    
    return ambient + diffuse + specular;
}

vec3 pointPhong(PointLight light, vec3 normal, vec3 viewingDirection) {
    vec3 lightDirection = normalize(light.position - fPosition);
    vec3 reflectionDirection = reflect(-1.0 * lightDirection, normal);
    float lightDistance = length(light.position - fPosition);

    vec3 ambient = material.ambient * light.ambient;
    vec3 diffuse = material.diffuse * max(dot(normal, lightDirection), 0.0) * light.diffuse;
    vec3 specular = material.specular * pow(max(dot(viewingDirection, reflectionDirection), 0.0), material.shininess) * light.specular;

    float attenuation = 1.0f / (light.constantDecay + light.linearDecay * lightDistance + light.quadraticDecay * lightDistance * lightDistance);

    return (ambient + diffuse + specular) * attenuation;
}

void main() {
	if (lightingEnabled) {
        vec3 normal = normalize(fNormal);
        vec3 viewingDirection = normalize(cameraPosition - fPosition);
	
	    // Directional Light (Sun)
	    vec3 calculatedColor = directionalPhong(sun, normal, viewingDirection);
	    
	    // Point Lights
	    if (fPosition.z >= 0) { // Ein kleiner Trick um die Leuchtreklame nicht nach hinten leuchten zu lassen
            for (int i = 0; i < nPointLights; i++)
	        calculatedColor += pointPhong(pointLights[i], normal, viewingDirection);
        }
        
	    fColor = vec4(calculatedColor * objectColor.rgb, objectColor.a);
    }
    else
		fColor = objectColor;
		
	if (texturingEnabled)
    	fColor *= texture(textureData, fTexCoord);
}

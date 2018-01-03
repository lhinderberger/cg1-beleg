#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Billboard.h"

using namespace cg1;
using namespace glm;
using namespace std;
    
const int nCharacters = 6;

class cg1::Bulb : public Cylinder {
private:
    vec3 position;
public:
    Bulb(Application * application, const vec3 & position)
    : position(position), Cylinder(application, 0.025, 0.05, 64) {
        material.ambient = vec3(0.5);
        material.diffuse = vec3(0.3);
        material.specular = vec3(1.0);
        material.shininess = 64;
        
        setColor(vec4(1.0f,0.0f,0.0f,0.5f));
        modelMatrix = translate(mat4(1.0f), position);
        modelMatrix = rotate(modelMatrix, radians(90.0f), vec3(1,0,0));
    }
    
    inline const vec3 & getPosition() const { return position; }
};

Billboard::Billboard(Application * application) : Model(application) {
    static const int nRows = 9;
    static const unsigned char pattern[nRows][nCharacters] = {
        {0b00111100, 0b00000000, 0b00000000, 0b00000000, 0b00111110, 0b10000000},
        {0b01000010, 0b00000000, 0b00000000, 0b00000000, 0b01000001, 0b10000000},
        {0b10000001, 0b00000000, 0b00000000, 0b00000000, 0b10000000, 0b10000000},
        {0b10000001, 0b01111100, 0b00110000, 0b00011000, 0b10001111, 0b10000000},
        {0b10000001, 0b01000010, 0b01001000, 0b00100100, 0b10001001, 0b10000000},
        {0b01000010, 0b01000010, 0b01110000, 0b00100100, 0b10000001, 0b10000000},
        {0b00111100, 0b01111100, 0b00111000, 0b00100100, 0b01111110, 0b11111100},
        {0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000},
        {0b00000000, 0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}
    };
    
    // Assemble Character Bulbs
    activeCharacters.resize(nCharacters);
    characterBulbs.resize(nCharacters);
    
    for (int row = 0; row < nRows; row++) {
        for (int c = 0; c < nCharacters; c++) {
            for (int col = 0; col < 8; col++) {
                if (pattern[row][c] & (0b10000000>>col)) {
                    vec3 position(c*8*0.1 + col * 0.075, 0.2f+(nRows-row) * 0.1, 0);
                    characterBulbs[c].emplace_back(new Bulb(getApplication(), position));
                }
            }
        }
    }
    
    // Assemble Backplane
    Cuboid * bpCuboid = new Cuboid(getApplication(), nCharacters * 0.81f, nRows * 0.15f, 0.05f);
    bpCuboid->modelMatrix = translate(mat4(1.0f), vec3(-0.2f,0.05f, -0.05f));
    bpCuboid->setColor(vec4(0.1f,0.1f,0.1f,1.0f));
    backplane.emplace_back(bpCuboid);
    
    //Debug
    activeCharacters[0] = true;
}


list<PointLight> Billboard::getPointLights() {
    list<PointLight> pointLights;
    
    PointLight bulbLight;
    bulbLight.ambient = vec3(0.3f,0.03f,0.03f);
    bulbLight.diffuse = vec3(1.0f,0.1f,0.1f);
    bulbLight.specular = vec3(0.2f,0.02f,0.02f);
    bulbLight.constantDecay = 1.0f;
    bulbLight.linearDecay = 0.95f;
    bulbLight.quadraticDecay = 10.0f;
            
    for (int c = 0; c < nCharacters; c++) {
    	if (activeCharacters[c]) {
    		for (unique_ptr<Bulb> & bulb : characterBulbs[c]) {
    		    bulbLight.position = bulb->getPosition();
    		    pointLights.push_back(bulbLight);
    		}
        }
    }
    
    return pointLights;
}

void Billboard::render(glm::mat4 parentModelMatrix) {
	Application * application = getApplication();
    bool lightingEnabled = application->getLightingEnabled();
    
    // Render backplane
    for (unique_ptr<Cuboid> & cuboid : backplane)
        cuboid->render(modelMatrix);
    
    // Render inactive bulbs
    for (int c = 0; c < nCharacters; c++) {
    	if (!activeCharacters[c]) {
    		for (unique_ptr<Bulb> & bulb : characterBulbs[c])
		        bulb->render(modelMatrix);
        }
    }
    
    
    // Render active bulbs without lighting
    application->setLightingEnabled(false);
    for (int c = 0; c < nCharacters; c++) {
    	if (activeCharacters[c]) {
    		for (unique_ptr<Bulb> & bulb : characterBulbs[c])
		        bulb->render(modelMatrix);
        }
    }
    application->setLightingEnabled(lightingEnabled);
}

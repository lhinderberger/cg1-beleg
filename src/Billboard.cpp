#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Billboard.h"

using namespace cg1;
using namespace glm;
using namespace std;

Billboard::Billboard(){
    static const int nCharacters = 6;
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
    
    for (int row = 0; row < nRows; row++) {
        for (int c = 0; c < nCharacters; c++) {
            for (int col = 0; col < 8; col++) {
                if (pattern[row][c] & (0b10000000>>col)) {
                    Cylinder * bulb = new Cylinder(0.025, 0.05, 16);
                    bulb->modelMatrix = translate(bulb->modelMatrix, vec3(c*8*0.1 + col * 0.075, (nRows-row) * 0.1, 0));
                    bulb->modelMatrix = rotate(bulb->modelMatrix, radians(90.0f), vec3(1,0,0));
                    bulbs.emplace_back(bulb);
                }
            }
        }
    }
}


void Billboard::render(glm::mat4 parentModelMatrix) {
    Model::render(parentModelMatrix);
    for (unique_ptr<Cylinder> & bulb: bulbs)
        bulb->render(modelMatrix);
}

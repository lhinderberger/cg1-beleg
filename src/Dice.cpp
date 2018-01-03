#include "Dice.h"
#include "Texture.h"

using namespace cg1;
using namespace glm;

static Texture * texture = nullptr;

Dice::Dice(Application * application, float sideLength)
    : Cuboid(application, sideLength, sideLength, sideLength) {
    
    if (!texture)
        texture = new Texture("wuerfel.png");
}


void Dice::render(mat4 parentModelMatrix) {
    getApplication()->setTexturingEnabled(true);
    texture->bind();
    Cuboid::render();
    getApplication()->setTexturingEnabled(false);
}

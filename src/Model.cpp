#include "Model.h"

using namespace cg1;
using namespace glm;

const glm::mat4 & Model::getModelMatrix() {
    if (modified)
        updateModelMatrix();
    return modelMatrix;
}

void Model::updateModelMatrix() {
    //TODO
    modified = false;
}

vec4 Model::setColor(const vec4 & color) {
    this->color = color;
}
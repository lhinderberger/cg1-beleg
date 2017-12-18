#include "Model.h"

using namespace cg1;

const glm::mat4 & Model::getModelMatrix() {
    if (modified)
        updateModelMatrix();
    return modelMatrix;
}

void Model::updateModelMatrix() {
    //TODO
    modified = false;
}
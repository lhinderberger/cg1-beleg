#include <GL/glew.h>
#include "Model.h"

using namespace cg1;
using namespace glm;

GLuint Model::modelMatrixLocation = 0;


void Model::render(glm::mat4 parentModelMatrix) {
    mat4 renderModelMatrix = parentModelMatrix * modelMatrix;
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &renderModelMatrix[0][0]);
}

vec4 Model::setColor(const vec4 & color) {
    this->color = color;
}

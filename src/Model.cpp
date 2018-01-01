#include <cassert>
#include <GL/glew.h>
#include "Model.h"

using namespace cg1;
using namespace glm;

Model::Model(Application * application) {
	assert(application);
	this->application = application;
}


void Model::render(glm::mat4 parentModelMatrix) {
    mat4 renderModelMatrix = parentModelMatrix * modelMatrix;
    glUniformMatrix4fv(application->getModelMatrixLocation(), 1, GL_FALSE, &renderModelMatrix[0][0]);
}

vec4 Model::setColor(const vec4 & color) {
    this->color = color;
}

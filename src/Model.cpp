#include <cassert>
#include <GL/glew.h>
#include "Model.h"

using namespace cg1;
using namespace glm;

Model::Model(Application * application) {
	assert(application);
	this->application = application;
}


vec4 Model::setColor(const vec4 & color) {
    this->color = color;
}

void Model::setModelAndNormalMatrixUniform(mat4 processedModelMatrix) {
    glUniformMatrix4fv(
        application->getModelMatrixLocation(), 1, GL_FALSE,
        &processedModelMatrix[0][0]
    );
    mat4 normalMatrix = mat3(transpose(inverse(processedModelMatrix)));
    glUniformMatrix3fv(
        application->getNormalMatrixLocation(), 1, GL_FALSE,
        &normalMatrix[0][0]
    );
}

#include <GL/glew.h>

#include "VAO.h"

#include <iostream>

using namespace cg1;
using namespace std;

VAO::VAO(const GLfloat * data, int nData) {
    this->nData = nData;

    // Generate array buffer for raw vertex data
    glGenBuffers(1, &vboId);

    // Generate the actual vertex array object
	glGenVertexArrays(1, &vaoId);

    // Bind and load vertex data
	glBindVertexArray(vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * nData, data, GL_STATIC_DRAW);
}

VAO::~VAO() {
    // Remove VAO, then VBO
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &vboId);
}

unique_ptr<VAO> VAO::create(const GLfloat * data, int nData) {
    return unique_ptr<VAO>(new VAO(data, nData));
}


void VAO::bind() {
    glBindVertexArray(vaoId);
}

void VAO::setupAttribPointer(int index, int size, int stride, int offset, bool normalized) {
    glVertexAttribPointer(
        index, size, GL_FLOAT, normalized ? GL_TRUE : GL_FALSE,
        stride * sizeof(GLfloat), (void*)(offset * sizeof(GLfloat))
    );
	glEnableVertexAttribArray(index);
}

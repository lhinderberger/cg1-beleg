#include <GL/glew.h>

#include "VAO.h"

#include <iostream>

using namespace cg1;
using namespace std;

VAO::VAO(const GLfloat * vertices, int nVertices, int components) {
    this->components = components;
    this->nVertices = nVertices;

    // Generate array buffer for raw vertex data
    glGenBuffers(1, &vboId);

    // Generate the actual vertex array object
	glGenVertexArrays(1, &vaoId);

    // Bind and load vertex data
	glBindVertexArray(vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * components * nVertices, vertices, GL_STATIC_DRAW);

    // Setup default attributes for vertex shader
    // Position argument #0
    glVertexAttribPointer(0, components, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
}

VAO::~VAO() {
    // Remove VAO, then VBO
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &vboId);
}

unique_ptr<VAO> VAO::create(const GLfloat *vertices, int nVertices, int components) {
    return unique_ptr<VAO>(new VAO(vertices, nVertices, components));
}

unique_ptr<VAO> VAO::create(const std::vector<glm::vec2> & vertices) {
    return create((const float*)&vertices[0], vertices.size(), 2);
}

unique_ptr<VAO> VAO::create(const std::vector<glm::vec3> & vertices) {
    return create((const float*)&vertices[0], vertices.size(), 3);
}


void VAO::bind() {
    glBindVertexArray(vaoId);
}

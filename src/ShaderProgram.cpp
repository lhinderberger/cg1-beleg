#include <GL/glew.h>

#include <iostream>
#include <vector>

#include "ShaderProgram.h"
#include "GLException.h"

using namespace cg1;
using namespace std;

ShaderProgram::ShaderProgram() {
    id = glCreateProgram();
    if (!id)
        throw GLException();
}

ShaderProgram::~ShaderProgram() {
    if (id)
        glDeleteProgram(id);
}

GLuint ShaderProgram::getId() const {
    return id;
}

void ShaderProgram::use() {
    glUseProgram(id);
}



void ShaderProgramFactory::addShader(AbstractShader * shader) {
    shaders.push_back(shader);
}

unique_ptr<ShaderProgram> ShaderProgramFactory::link() {
    unique_ptr<ShaderProgram> result(new ShaderProgram());
    GLuint programId = result->getId();

    // Attach every shader we have remembered to the ShaderProgram
    for (const AbstractShader * shader : shaders)
        glAttachShader(programId, shader->getId());

    // Link and check for errors
    glLinkProgram(programId);
    GLint success = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
        printLinkErrorLog(programId);

    // Detach all the shaders again
    for (const AbstractShader * shader : shaders)
        glDetachShader(programId, shader->getId());

    return result;
}

void ShaderProgramFactory::printLinkErrorLog(GLuint programId) {
    //FIXME: Code duplication with Shader.cpp
    // Retrieve log entry from OpenGL in an annoyingly complicated fashion
    GLint logLength = 0;
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
	vector<GLchar> errorLog(logLength);
	glGetProgramInfoLog(programId, logLength, &logLength, &errorLog[0]);

    // Output a nice error message
    cerr << "ERROR linking shaders: " << (const GLchar*)&errorLog[0] << endl;
    throw runtime_error("Shader program linking aborted");
}

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <GL/glew.h>

#include "Shader.h"
#include "GLException.h"

#define SOURCECODE_BUFFER_SIZE 1024

using namespace cg1;
using namespace std;

AbstractShader::AbstractShader(GLenum type, istream & source, const string & name) {
    this->name = name;
    this->type = type;
    compile(source);
}

AbstractShader::AbstractShader(GLenum type, const string & filename) {
    name = filename;

    // Try to open file
    ifstream f(filename);
    if (!f.good()) {
        printErrorMessageTitle();
        cerr << "Could not open file!" << endl;
        throw runtime_error("Error compiling shader: Could not open file!");
    }

    // Trigger compilation
    this->type = type;
    compile(f);
}

AbstractShader::~AbstractShader() {
    if (id != 0)
        glDeleteShader(id);
}


void AbstractShader::compile(istream & source) {
    // Reserve space
    id = glCreateShader(type);
    if (!id)
        throw GLException();

    // Read source code into memory
    string sourceCode;
    char buffer[SOURCECODE_BUFFER_SIZE];
    while (!source.eof()) {
        source.read(buffer, 1024);
        int nRead = source.gcount();
        sourceCode.append(buffer, nRead);
    }


    // Set source code for shader

    // Note: OpenGL API requires passing arrays here, so that explains the
    // rather weird syntax.
    const char * shaderSourceC = sourceCode.c_str();
    GLint shaderSourceLength = sourceCode.length();
    glShaderSource(id, 1, &shaderSourceC, &shaderSourceLength);


    // Compile shader and notify about potential errors
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
        printCompileErrorLog();
}

bool AbstractShader::getCompileSuccess() const {
    return success == GL_TRUE;
}

GLuint AbstractShader::getId() const {
    return id;
}

GLenum AbstractShader::getType() const {
    return type;
}

void AbstractShader::printCompileErrorLog() {
    // Retrieve log entry from OpenGL in an annoyingly complicated fashion
    GLint logLength = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
    vector<GLchar> errorLog(logLength);
    glGetShaderInfoLog(id, logLength, &logLength, &errorLog[0]);

    // Output a nice error message
    printErrorMessageTitle();
    cerr << (const GLchar*)(&errorLog[0]) << endl;
    throw runtime_error("Compilation aborted due to errors in the shader!");
}

void AbstractShader::printErrorMessageTitle() {
    cerr << "ERROR compiling shader " << name << ": ";
}

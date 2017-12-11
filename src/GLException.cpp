#include "GLException.h"

#include <GL/gl.h>

using namespace cg1;
using namespace std;

GLException::GLException()
    : runtime_error("Error in OpenGL") {
    // Build extended Error Message
    extendedMessage = "Error in OpenGL - Error flags set:\n\n";
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        string subMessage = "";
        if (err == GL_INVALID_ENUM)
            subMessage = "Invalid Enum";
        else if (err == GL_INVALID_VALUE)
            subMessage = "Invalid Value";
        else if (err == GL_INVALID_OPERATION)
            subMessage = "Invalid Operation";
        else if (err == GL_INVALID_FRAMEBUFFER_OPERATION)
            subMessage = "Invalid Value";
        else if (err == GL_OUT_OF_MEMORY)
            subMessage = "Out of Memory";
        else if (err == GL_STACK_UNDERFLOW)
            subMessage = "Stack Underflow";
        else if (err == GL_STACK_OVERFLOW)
            subMessage = "Stack Overflow";
        else
            subMessage = "Unknown error";

            extendedMessage += subMessage + "\n";
    }
}


const char * GLException::what() const noexcept {
    return extendedMessage.c_str();
}

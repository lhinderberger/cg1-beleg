#ifndef CG1_SHADERPROGRAM_H
#define CG1_SHADERPROGRAM_H

#include <list>
#include <memory>
#include <GL/glew.h>

#include "Shader.h"

namespace cg1 {
    class ShaderProgramFactory;

    /**
     * Wraps around an OpenGL Shader Program and takes care of its automatic
     * destruction.
     */
    class ShaderProgram {
        friend class ShaderProgramFactory;
    private:
        GLuint id = 0;

        ShaderProgram();
    public:
        ~ShaderProgram();

        void use();
        inline GLuint getId() const { return id; }
    };

    /**
     * Creates a ShaderProgram by linking together multiple Shader instances
     */
    class ShaderProgramFactory {
    private:
        std::list<AbstractShader*> shaders;

        void printLinkErrorLog(GLuint programId);

    public:
        /** Adds a Shader that is to be linked into the ShaderProgram */
        void addShader(AbstractShader * shader);

        /**
         * Links the ShaderProgram as recommended in the OpenGL documentation.
         * The individual Shader instances do not need to outlive the generated
         * ShaderProgram.
         */
        std::unique_ptr<ShaderProgram> link();
    };
}

#endif

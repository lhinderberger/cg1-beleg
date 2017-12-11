#ifndef CG1_SHADER_H
#define CG1_SHADER_H

#include <istream>
#include <string>

#include <GL/gl.h>

/**
 * This macro is the quick and easy way to define a new AbstractShader subtype
 * with default behaviour.
 */
#define DEF_SHADER(CLASSNAME, SHADER_TYPE) class CLASSNAME : public AbstractShader {\
public:\
    CLASSNAME(std::istream & source, const std::string & name = "")\
        : AbstractShader(SHADER_TYPE, source, name) {}\
    CLASSNAME(const std::string & filename)\
        : AbstractShader(SHADER_TYPE, filename) {}\
};

namespace cg1 {
    /**
     * Represents a Shader loaded and compiled from an arbitrary input stream.
     * See the concrete implementations below, whose names match those defined
     * by OpenGL.
     */
    class AbstractShader {
    private:
        GLenum type = 0;
        GLint success = 0;
        GLuint id = 0;
        std::string name;

        void compile(std::istream & source);
        void printCompileErrorLog();
        void printErrorMessageTitle();

    protected:
        /**
         * Load and compile a shader from an arbitrary input stream.
         * @param type   The GL shader type that will be passed to glCreateShader()
         * @param source A source stream of your choice containing the shader source code.
         *               It will be read entirely.
         * @param name   An optional name to help with recognition in error logs.
         */
        AbstractShader(GLenum type, std::istream & source, const std::string & name = "");

        /**
         * Load a shader directly from file.
         * Wraps around AbstractShader(GLenum, istream, string).
         */
        AbstractShader(GLenum type, const std::string & filename);
        virtual ~AbstractShader();

    public:
        bool getCompileSuccess() const;
        GLuint getId() const;
        GLenum getType() const;
    };

    DEF_SHADER(ComputeShader, GL_COMPUTE_SHADER);
    DEF_SHADER(FragmentShader, GL_FRAGMENT_SHADER);
    DEF_SHADER(GeometryShader, GL_GEOMETRY_SHADER);
    DEF_SHADER(TessControlShader, GL_TESS_CONTROL_SHADER);
    DEF_SHADER(TessEvaluationShader, GL_TESS_EVALUATION_SHADER);
    DEF_SHADER(VertexShader, GL_VERTEX_SHADER);
}

#endif

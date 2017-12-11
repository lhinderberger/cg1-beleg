#ifndef CG1_VAO_H
#define CG1_VAO_H

#include <memory>
#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

namespace cg1 {
    /**
     * Encapsulates a Vertex Array Object
     */
    class VAO {
    private:
        int components = 0, nVertices = 0;
        GLuint vaoId = 0, vboId = 0;
        
        VAO(const GLfloat * vertices, int nVertices, int components = 3);
        VAO & operator=(const VAO&) = delete;
        VAO(const VAO&) = delete;
    public:
        ~VAO();

        static std::unique_ptr<VAO> create(const GLfloat * vertices, int nVertices, int components);
        static std::unique_ptr<VAO> create(const std::vector<glm::vec2> & vertices);
        static std::unique_ptr<VAO> create(const std::vector<glm::vec3> & vertices);

        void bind();

        inline int getComponents() const { return components; }
        inline int getNVertices() const { return nVertices; }
        inline GLuint getVAOId() const { return vaoId; }
        inline GLuint getVBOId() const { return vboId; }
    };
}

#endif

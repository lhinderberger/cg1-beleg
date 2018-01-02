#ifndef CG1_VAO_H
#define CG1_VAO_H

#include <memory>
#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>

namespace cg1 {
    /**
     * Encapsulates a Simple Vertex Array Object
     */
    class VAO {
    private:
        int nData = 0;
        GLuint vaoId = 0, vboId = 0;
        
        VAO(const GLfloat * data, int nData);
        VAO & operator=(const VAO&) = delete;
        VAO(const VAO&) = delete;
    public:
        ~VAO();

        static std::unique_ptr<VAO> create(const GLfloat * data, int nData);

        void bind();
        void setupAttribPointer(
            int index, int size,
            int stride = 0, int offset = 0, bool normalized = false
        );

        inline int getNData() const { return nData; }
        inline GLuint getVAOId() const { return vaoId; }
        inline GLuint getVBOId() const { return vboId; }
    };
}

#endif

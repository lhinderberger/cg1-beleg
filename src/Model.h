#ifndef CG1_MODEL
#define CG1_MODEL

#include <GL/gl.h>
#include <glm/glm.hpp>

namespace cg1 {
    class Model {
    private:
        glm::vec4 color = glm::vec4(1.0f,1.0f,1.0f,1.0f);
        
    protected:

    public:
        static GLuint modelMatrixLocation;
        glm::mat4 modelMatrix;

        virtual void render(glm::mat4 parentModelMatrix = glm::mat4());
        glm::vec4 setColor(const glm::vec4 & color);

        const inline glm::vec4 & getColor() const { return color; }
    };
};

#endif

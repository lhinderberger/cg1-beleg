#ifndef CG1_MODEL
#define CG1_MODEL

#include <glm/glm.hpp>

namespace cg1 {
    class Model {
    private:
        bool modified = true;
        glm::mat4 modelMatrix;
        glm::vec4 color = glm::vec4(1.0f,1.0f,1.0f,1.0f);
        
        void updateModelMatrix();
        
    public:
        virtual void render() = 0;
        const glm::mat4 & getModelMatrix();
        glm::vec4 setColor(const glm::vec4 & color);
        
        const inline glm::vec4 & getColor() const { return color; }
    };
};

#endif

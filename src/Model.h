#ifndef CG1_MODEL
#define CG1_MODEL

#include <glm/glm.hpp>

namespace cg1 {
    class Model {
    private:
        bool modified = true;
        glm::mat4 modelMatrix;
        
        void updateModelMatrix();
        
    public:
        virtual void render() = 0;
        const glm::mat4 & getModelMatrix();
    };
};

#endif

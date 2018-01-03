#ifndef CG1_PLANE
#define CG1_PLANE

#include <memory>

#include "Model.h"
#include "VAO.h"

namespace cg1 {
    class Plane : public Model {
    private:
        std::unique_ptr<VAO> vao;
    
    public:
        Material material;
        
        Plane(Application * application, float width, float depth);
        
        virtual void render(glm::mat4 parentModelMatrix = glm::mat4()) override;
    };
}

#endif

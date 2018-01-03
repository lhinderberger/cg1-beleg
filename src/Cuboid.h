#ifndef CG1_CUBOID
#define CG1_CUBOID

#include <memory>

#include "Model.h"
#include "VAO.h"

namespace cg1 {
    class Cuboid : public Model {
    private:
        std::unique_ptr<VAO> vao;
    
    public:
        Material material;
        
        Cuboid(Application * application, float width, float height, float depth);
        
        virtual void render(glm::mat4 parentModelMatrix = glm::mat4()) override;
    };
}

#endif

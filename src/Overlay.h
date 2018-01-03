#ifndef CG1_OVERLAY
#define CG1_OVERLAY

#include <memory>

#include "Model.h"
#include "VAO.h"

namespace cg1 {
    class Overlay : public Model {
    private:
        std::unique_ptr<VAO> vao;
    
    public:
        Material material;
        
        Overlay(Application * application);
        
        virtual void render(glm::mat4 parentModelMatrix = glm::mat4()) override;
    };
}

#endif

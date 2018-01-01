#ifndef CG1_AXISES
#define CG1_AXISES

#include "Model.h"
#include "VAO.h"

namespace cg1 {
    class Axises : public Model {
    private:
        std::unique_ptr<VAO> vao;
    
    public:
        Axises(Application * application, float length = 1000.0f);
        virtual void render(glm::mat4 parentModelMatrix = glm::mat4()) override;
    };
};

#endif

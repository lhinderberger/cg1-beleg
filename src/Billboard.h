#ifndef CG1_BILLBOARD_H
#define CG1_BILLBOARD_H

#include "Model.h"
#include "Cuboid.h"
#include "Cylinder.h"

#include <memory>
#include <vector>

namespace cg1 {
    class Billboard : public Model {
    private:
        GLuint modelMatrixLocation;
        std::vector<std::unique_ptr<Cuboid>> backplane;
        std::vector<std::vector<std::unique_ptr<Cylinder>>> characterBulbs;
        std::vector<bool> activeCharacters;
        
    public:
        Billboard(Application * application);
        
        virtual void render(glm::mat4 parentModelMatrix = glm::mat4()) override;
    };
};

#endif

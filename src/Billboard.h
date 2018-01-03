#ifndef CG1_BILLBOARD_H
#define CG1_BILLBOARD_H

#include "Model.h"
#include "Cuboid.h"
#include "Cylinder.h"

#include <memory>
#include <vector>

namespace cg1 {
    class Bulb;
    
    class Billboard : public Model {
    private:
        int animationStep = 0;
        int pattern = 0;
        
        GLuint modelMatrixLocation;
        std::vector<std::unique_ptr<Cuboid>> backplane;
        std::vector<std::vector<std::unique_ptr<Bulb>>> characterBulbs;
        std::vector<std::unique_ptr<Bulb>> passiveBulbs;
        std::vector<bool> activeCharacters;
        
    public:
        Billboard(Application * application);
        
        void step();
        void cyclePattern();
        
        virtual std::list<PointLight> getPointLights() override;
        virtual void render(glm::mat4 parentModelMatrix = glm::mat4()) override;
    };
};

#endif

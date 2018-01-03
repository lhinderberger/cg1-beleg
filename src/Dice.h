#ifndef CG1_DICE_H
#define CG1_DICE_H

#include "Cuboid.h"

namespace cg1 {    
    class Dice : public Cuboid {        
    public:
        Dice(Application * appliation, float sideLength);
        
        virtual void render(glm::mat4 parentModelMatrix = glm::mat4()) override;
    };
};

#endif

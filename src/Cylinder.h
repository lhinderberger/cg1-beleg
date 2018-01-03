#ifndef CG1_CYLINDER_H
#define CG1_CYLINDER_H

#include <memory>

#include "Model.h"
#include "VAO.h"

namespace cg1 {
    class Cylinder : public Model {
    private:
        std::unique_ptr<VAO> sideVAO, capVAO;
        float radius, height;
        int subdivisions;

    public:
        Material material;
        
        Cylinder(Application * application, float radius, float height, int subdivisions);

        virtual void render(glm::mat4 parentModelMatrix = glm::mat4()) override;
        
        inline int getSubdivisions() const { return subdivisions; };
        inline float getRadius() const { return radius; };
        inline float getHeight() const { return height; };
    };
}

#endif

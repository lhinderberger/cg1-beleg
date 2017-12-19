#ifndef CG1_CYLINDER_H
#define CG1_CYLINDER_H

#include <memory>
#include <vector>

#include "Model.h"
#include "VAO.h"

namespace cg1 {
    class Cylinder : public Model {
    private:
        std::unique_ptr<VAO> vao;
        int nVertices;
        std::vector<int> triangleIndexes, triangleStripIndexes;

    public:
        Cylinder(float radius, float height, int subdivisions);

        virtual void render() override;
    };
}

#endif

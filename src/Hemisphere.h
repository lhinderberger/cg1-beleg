#ifndef CG1_HEMISPHERE_H
#define CG1_HEMISPHERE_H

#include <memory>

#include "Model.h"
#include "VAO.h"

namespace cg1 {
    class Hemisphere : public Model {
    private:
        std::unique_ptr<VAO> vao;

    public:
        Hemisphere(float radius);

        virtual void render() override;
    };
}

#endif

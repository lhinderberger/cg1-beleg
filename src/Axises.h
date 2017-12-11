#ifndef CG1_AXISES
#define CG1_AXISES

#include "Renderable.h"
#include "VAO.h"

namespace cg1 {
    class Axises : public Renderable {
    private:
        std::unique_ptr<VAO> vao;
    
    public:
        Axises(float length = 1000.0f);
        virtual void render() override;
    };
};

#endif

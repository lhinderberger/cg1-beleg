#ifndef CG1_MATERIAL_H
#define CG1_MATERIAL_H

#include <glm/glm.hpp>

namespace cg1 {
    class Material {
    public:
        glm::vec3 ambient = glm::vec3(0.1f);
        glm::vec3 specular = glm::vec3(0.5f);
        glm::vec3 diffuse = glm::vec3(1.0f);
        float shininess = 1.0f;
    };
};

#endif

#ifndef CG1_LIGHT_H
#define CG1_LIGHT_H

#include <glm/glm.hpp>

namespace cg1 {
    class DirectionalLight {
    public:
        glm::vec3 direction = glm::vec3(0.2f, -1.0f, -0.2f);
        glm::vec3 ambient = glm::vec3(0.1f);
        glm::vec3 specular = glm::vec3(0.5f);
        glm::vec3 diffuse = glm::vec3(1.0f);
    };
};

#endif

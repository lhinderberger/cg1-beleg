#ifndef CG1_FIRST_PERSON_CAMERA_H
#define CG1_FIRST_PERSON_CAMERA_H

#include <glm/glm.hpp>

namespace cg1 {
    class FirstPersonCamera {
    private:
        bool modified = true;
        float pitch = 0.0f, yaw = 0.0f;
    
        glm::mat4 viewMatrix;
        glm::vec3 position = glm::vec3(0.0f,0.2f,1.0f);
        
        void updateViewMatrix();
        
    public:        
        const glm::mat4 & getViewMatrix();
        void moveInYawDirection(const glm::vec3 & distance);
        void setPitch(float pitch);
        void setPosition(const glm::vec3 & position);
        void setYaw(float yaw);
                
        inline float getPitch() const { return pitch; }
        inline const glm::vec3 & getPosition() const { return position; }
        inline float getYaw() const { return yaw; }
    };
}

#endif

#include "FirstPersonCamera.h"
#include <glm/gtx/transform.hpp>
#include <iostream>


using namespace cg1;
using namespace glm;
using namespace std;

const mat4 & FirstPersonCamera::getViewMatrix() {
    if (modified)
        updateViewMatrix();
    return viewMatrix;
}

void FirstPersonCamera::moveInYawDirection(const vec3 & distance) {
    mat4 yawRotationMatrix = rotate(-1.0f * yaw, vec3(0.0,1.0,0.0));
    vec3 newPosition = getPosition() + vec3(yawRotationMatrix * vec4(distance,1.0));    
    setPosition(newPosition);
}

void FirstPersonCamera::setPitch(float pitch) {
    this->pitch = pitch;
    modified = true;
}

void FirstPersonCamera::setPosition(const vec3 & position) {
    this->position = position;
    modified = true;
}

void FirstPersonCamera::setYaw(float yaw) {
    this->yaw = yaw;
    modified = true;
}

void FirstPersonCamera::updateViewMatrix() {
    viewMatrix = rotate(pitch, vec3(1.0,0.0,0.0)) * rotate(yaw, vec3(0.0,1.0,0.0))
        * translate(-1.0f * position);
    modified = false;
}

#include <GL/freeglut.h>
#include "InteractiveFirstPersonCamera.h"

using namespace cg1;
using namespace glm;

void InteractiveFirstPersonCamera::processKey(unsigned char key) {
    //Do nothing
}

void InteractiveFirstPersonCamera::processRelativeMouseMotion(float x, float y) {
    float adjFactor = radians(180.0f);
    setYaw(getYaw() + x * adjFactor);
    setPitch(getPitch() + y * adjFactor);
}

void InteractiveFirstPersonCamera::processSpecialKey(int key) {
    float speed = 0.01f;
    
    if (key == GLUT_KEY_UP)
        moveInYawDirection(vec3(0.0f, 0.0f, -1.0f * speed));
    else if (key == GLUT_KEY_DOWN)
        moveInYawDirection(vec3(0.0f, 0.0f, speed));
    else if (key == GLUT_KEY_LEFT)
        moveInYawDirection(vec3(-1.0f * speed, 0.0f, 0.0f));
    else if (key == GLUT_KEY_RIGHT)
        moveInYawDirection(vec3(speed, 0.0f, 0.0f));
}
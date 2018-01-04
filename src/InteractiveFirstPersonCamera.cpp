#include <cmath>
#include <iostream>
#include <GL/freeglut.h>
#include "InteractiveFirstPersonCamera.h"

// Limit Pitch to 90 degrees in order to avoid "flipping over" the camera
#define MAX_PITCH_RADIANS 1.5708

using namespace cg1;
using namespace glm;

void InteractiveFirstPersonCamera::processKey(unsigned char key) {
    float speed = 0.05f;
    
    if (key == 'w')
        moveInYawDirection(vec3(0.0f, 0.0f, -1.0f * speed));
    else if (key == 's')
        moveInYawDirection(vec3(0.0f, 0.0f, speed));
    else if (key == 'a')
        moveInYawDirection(vec3(-1.0f * speed, 0.0f, 0.0f));
    else if (key == 'd')
        moveInYawDirection(vec3(speed, 0.0f, 0.0f));

}

void InteractiveFirstPersonCamera::processRelativeMouseMotion(float x, float y) {
    float adjFactor = radians(180.0f);
    setYaw(getYaw() + x * adjFactor);
    
    float newPitch = getPitch() + y * adjFactor;
    if (fabs(newPitch) > MAX_PITCH_RADIANS)
    	newPitch = newPitch < 0 ? -1.0f * MAX_PITCH_RADIANS : MAX_PITCH_RADIANS;
    setPitch(newPitch);
}

void InteractiveFirstPersonCamera::processSpecialKey(int key) {
    float speed = 0.05f;
    
    if (key == GLUT_KEY_UP)
        moveInYawDirection(vec3(0.0f, 0.0f, -1.0f * speed));
    else if (key == GLUT_KEY_DOWN)
        moveInYawDirection(vec3(0.0f, 0.0f, speed));
    else if (key == GLUT_KEY_LEFT)
        moveInYawDirection(vec3(-1.0f * speed, 0.0f, 0.0f));
    else if (key == GLUT_KEY_RIGHT)
        moveInYawDirection(vec3(speed, 0.0f, 0.0f));
}

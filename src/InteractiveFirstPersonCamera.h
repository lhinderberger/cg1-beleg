#ifndef CG1_INTERACTIVE_FIRST_PERSON_CAMERA_H
#define CG1_INTERACTIVE_FIRST_PERSON_CAMERA_H

#include "FirstPersonCamera.h"

namespace cg1 {
    class InteractiveFirstPersonCamera : public FirstPersonCamera {
    public:
        void processKey(unsigned char key);
        void processRelativeMouseMotion(float x, float y);
        void processSpecialKey(int key);
    };
}

#endif

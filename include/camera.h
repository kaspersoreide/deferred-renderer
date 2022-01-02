#pragma once
#include "matrix.h"

class Camera {
public:
    Camera();
    void move();
    mat4 getView();

    vec3 pos, vel, spinVector;
    mat3 Rotation, Spin;
    bool mov[6], rot[6];
};
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;

struct Object {
    Object();
    void move();
    void setSpin(vec3 axis, float angle);
    mat3 getRotation();
    mat4 getModel();

    vec3 pos, vel;
    quat spin, rot;
    float size;
};
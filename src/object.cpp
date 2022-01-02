#include "object.h"

void Object::move() {
    rot = spin * rot;
    pos += vel;
}

mat3 Object::getRotation() {
    return mat3_cast(rot);
}

mat4 Object::getModel() {
    mat4 Model = mat4(getRotation() * size);
    Model[3] = vec4(pos.x, pos.y, pos.z, 1.0);
    return Model;
}

void Object::setSpin(vec3 axis, float angle) {
    spin = angleAxis(angle, axis);
}

Object::Object() {
    pos = vel = vec3(0.0f);
    rot = spin = quat(1.0f, 0.0f, 0.0f, 0.0f);
    size = 1.0f;
}
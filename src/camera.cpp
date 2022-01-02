#include "camera.h"

Camera::Camera() {
    Spin = Rotation = mat3(1.0f);
    pos = vel = spinVector = vec3(0.0f);
    for (int i = 0; i < 6; i++) {
        mov[i] = false;
        rot[i] = false;
    }
}

void Camera::move() {
    const float rotAmount = 0.0008f;
	const float movAmount = 0.0087f;
	vec3 right = Rotation * vec3(1.0, 0.0, 0.0);
	vec3 up = Rotation * vec3(0.0, 1.0, 0.0);
	vec3 forward = Rotation * vec3(0.0, 0.0, 1.0);
	if (rot[0]) spinVector += rotAmount * forward;
	if (rot[1]) spinVector -= rotAmount * forward;
	if (rot[2]) spinVector -= rotAmount * up;
	if (rot[3]) spinVector += rotAmount * up;
	if (rot[4]) spinVector -= rotAmount * right;
	if (rot[5]) spinVector += rotAmount * right;

	if (mov[0]) vel -= movAmount * forward;
	if (mov[1]) vel += movAmount * forward;
	if (mov[2]) vel -= movAmount * right;
	if (mov[3]) vel += movAmount * right;
	if (mov[4]) vel += movAmount * up;
	if (mov[5]) vel -= movAmount * up;
	/*
	if (dot(pos, pos) > 1000.0f) {
		vel -= 0.00002f * pos;
	}
	*/
	vel *= 0.99f;
	spinVector *= 0.99f;
    Spin = srotate(spinVector);
    Rotation = Spin * Rotation;
    pos += vel;
}

mat4 Camera::getView() {
    return inverse(translateR(Rotation, pos));
}
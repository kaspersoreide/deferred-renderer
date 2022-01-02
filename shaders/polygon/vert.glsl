#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 Model[128];
uniform mat4 VP;

out vec3 vNormal;
out vec3 wPos;
out vec3 center;
//const vec3 light = vec3(1.0, 0.0, 0.0);

void main() {
    //gl_Position = MVP * vec4(pos, 1.0);
    vec4 wp = Model[gl_InstanceID] * vec4(pos, 1.0);
    gl_Position = VP * wp;
	vNormal = normalize(vec3(Model[gl_InstanceID] * vec4(normal, 0.0)));
	wPos = vec3(wp);
	center = vec3(Model[3]);
}
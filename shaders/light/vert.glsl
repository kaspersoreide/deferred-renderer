#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 Model[128];
uniform vec3 color[128];
uniform mat4 VP;

out vec2 texCoords;
out vec3 center;
out vec3 lightColor;

//const vec3 light = vec3(1.0, 0.0, 0.0);

void main() {
    //gl_Position = MVP * vec4(pos, 1.0);
    lightColor = color[gl_InstanceID];
    vec4 wp = Model[gl_InstanceID] * vec4(pos, 1.0);
    center = Model[gl_InstanceID][3].xyz;
    vec4 screenPos = VP * wp;
    gl_Position = screenPos;
	texCoords = 0.5 * screenPos.xy + 0.5;
}
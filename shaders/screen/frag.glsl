#version 430

in vec2 texCoords;

uniform sampler2D gPos;
uniform sampler2D gNormal;
uniform sampler2D gColor;

out vec4 FragColor;

void main() {
    vec4 color = texture(gColor, texCoords);
    vec3 pos = vec3(texture(gPos, texCoords));
    vec3 normal = vec3(texture(gNormal, texCoords));
    FragColor = dot(normal, vec3(1.0, 0.0, 0.0)) * color;
}
#version 430

in vec2 texCoords;
in vec3 center;
in vec3 lightColor;

uniform sampler2D gPos;
uniform sampler2D gNormal;
uniform sampler2D gColor;

out vec4 FragColor;

void main() {
    vec2 coords = vec2(gl_FragCoord.x / 1280, gl_FragCoord.y / 720);
    vec4 color = texture(gColor, coords);
    vec3 pos = vec3(texture(gPos, coords));
    vec3 normal = vec3(texture(gNormal, coords));
    vec3 lightDir = center - pos;
    float lightAttenuation = 1.0 / (1.0 + dot(lightDir, lightDir));
    vec3 pixelColor = color.rgb * lightColor;
    FragColor = vec4(lightAttenuation * max(dot(normal, lightDir), 0.01) * pixelColor, 1.0) + 0.01;
    
}
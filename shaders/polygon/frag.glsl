#version 430

in vec3 vNormal;
in vec3 wPos;
in vec3 center;

layout(location = 0) out vec3 FragPos;
layout(location = 1) out vec3 FragNormal;
layout(location = 2) out vec4 FragColor;

void main() {
    /*
	vec3 lightDir = normalize(wPos - center);
	vec3 viewDir = normalize(wPos - cPos);
	vec3 reflectDir = reflect(lightDir, vNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
	vec3 specular = spec * pColor;
    */
    FragPos = wPos;
    FragNormal = vNormal;
	FragColor = vec4(1.0, 1.0, 1.0, 0.0);//vec4(specular, 1.0);
}
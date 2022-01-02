#include "lights.h"

LightArray::LightArray() {
    shader = loadShaders("shaders/light/vert.glsl", "shaders/light/frag.glsl");
    vertexArray = loadObject("objects/icosahedron.obj");
}

void LightArray::render(GBuffer gBuffer, mat4 VP) {
    glBindVertexArray(vertexArray);
	glUseProgram(shader);
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gBuffer.gPosition);
    glUniform1i(glGetUniformLocation(shader, "gPos"), 0);
    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gBuffer.gNormal);
    glUniform1i(glGetUniformLocation(shader, "gNormal"), 1);
    glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gBuffer.gColor);
    glUniform1i(glGetUniformLocation(shader, "gColor"), 2);
	
    
	glUniformMatrix4fv(glGetUniformLocation(shader, "VP"), 1, GL_FALSE, &VP[0][0]);    
	glUniformMatrix4fv(glGetUniformLocation(shader, "Model"), polygons.size(), GL_FALSE, &Models[0][0][0]);
    glUniform3fv(glGetUniformLocation(shader, "color"), colors.size(), &colors[0][0]);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glCullFace(GL_FRONT);
	GLint size = 0;
	//this gets size in bytes
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	//6 float attributes per vertex
	glDrawArraysInstanced(GL_TRIANGLES, 0, size / (6 * sizeof(float)), polygons.size());
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glCullFace(GL_BACK);
}

void LightArray::addPolygon(vec3 pos, float size, vec3 color) {
    PolygonArray::addPolygon(pos, size);
    colors.push_back(color);
}


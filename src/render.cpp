#include "render.h"

GLuint createQuadVAO() {
    GLuint VBO, quadVAO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	float data[] = {
		1.0, -1.0,
		1.0, 1.0,
		-1.0, 1.0,
		1.0, -1.0,
		-1.0, -1.0,
		-1.0, 1.0,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data[0], GL_STATIC_DRAW);
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		2,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(float),
		(void*)0
	);

    return quadVAO;
}

void illuminateScene(GLuint quadVAO, GBuffer gBuffer, GLuint shader) {
    glDisable(GL_DEPTH_TEST);
	glBindVertexArray(quadVAO);
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
	glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
}

void render(GLuint vertexArray, GLuint shader, int numVertices, mat4 Model, mat4 VP) {
    glUseProgram(shader);
    glBindVertexArray(vertexArray);
    glUniformMatrix4fv(glGetUniformLocation(shader, "Model"), 1, GL_FALSE, &Model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "VP"), 1, GL_FALSE, &VP[0][0]);
    mat4 MVP = VP * Model;
    glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

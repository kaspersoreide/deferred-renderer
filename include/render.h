#pragma once

#include "gbuffer.h"
#include <glm/glm.hpp>

using namespace glm;

GLuint createQuadVAO();

void render(GLuint vertexArray, GLuint shader, int numVertices, mat4 Model, mat4 VP);

void illuminateScene(GLuint quadVAO, GBuffer gBuffer, GLuint shader);
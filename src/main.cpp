#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <iostream>
#include <GL/glew.h>
#include <vector>
#include <chrono>
#include <math.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "gbuffer.h"
#include "loadshaders.h"
#include "loadOBJ.h"
#include "render.h"
#include "object.h"
#include "polygon.h"
#include "camera.h"
#include "lights.h"

using namespace std;
using namespace glm;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::duration<float> fsec;

//resolution of window in pixels
int SCR_WIDTH = 1280;
int SCR_HEIGHT = 720;

GLFWwindow* window;
Camera* cam;
bool closed = false, paused = false;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_E) {
		if (action == GLFW_PRESS) cam->rot[0] = true;
		if (action == GLFW_RELEASE) cam->rot[0] = false;
	}
	if (key == GLFW_KEY_Q) {
		if (action == GLFW_PRESS) cam->rot[1] = true;
		if (action == GLFW_RELEASE) cam->rot[1] = false;
	}
	if (key == GLFW_KEY_LEFT) {
		if (action == GLFW_PRESS) cam->rot[2] = true;
		if (action == GLFW_RELEASE) cam->rot[2] = false;
	}
	if (key == GLFW_KEY_RIGHT) {
		if (action == GLFW_PRESS) cam->rot[3] = true;
		if (action == GLFW_RELEASE) cam->rot[3] = false;
	}
	if (key == GLFW_KEY_UP) {
		if (action == GLFW_PRESS) cam->rot[4] = true;
		if (action == GLFW_RELEASE) cam->rot[4] = false;
	}
	if (key == GLFW_KEY_DOWN) {
		if (action == GLFW_PRESS) cam->rot[5] = true;
		if (action == GLFW_RELEASE) cam->rot[5] = false;
	}

	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS) cam->mov[0] = true;
		if (action == GLFW_RELEASE) cam->mov[0] = false;
	}
	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS) cam->mov[1] = true;
		if (action == GLFW_RELEASE) cam->mov[1] = false;
	}
	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS) cam->mov[2] = true;
		if (action == GLFW_RELEASE) cam->mov[2] = false;
	}
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS) cam->mov[3] = true;
		if (action == GLFW_RELEASE) cam->mov[3] = false;
	}
	if (key == GLFW_KEY_LEFT_SHIFT) {
		if (action == GLFW_PRESS) cam->mov[4] = true;
		if (action == GLFW_RELEASE) cam->mov[4] = false;
	}
	if (key == GLFW_KEY_LEFT_CONTROL) {
		if (action == GLFW_PRESS) cam->mov[5] = true;
		if (action == GLFW_RELEASE) cam->mov[5] = false;
	}
	if (key == GLFW_KEY_ESCAPE) closed = true;
}


int init() {
	// Initialise GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Test", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// Initialize GLEW
	//glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
    glPolygonMode(GL_FRONT, GL_FILL);
    //enable face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW); 

	int error = glGetError();

	if (error != GL_NO_ERROR) {
		cout << "OpenGL error: " << error << "\n";
	}

	glfwSetKeyCallback(window, keyCallback);

	return 0;
}

int main(void) {
    
	if (init() == -1) return -1;
    cam = new Camera();
    cam->pos = vec3(0.0f, 0.0f, 3.0f);
    GBuffer gBuffer;
    //GLuint icosahedron = loadObject("objects/icosahedron.obj");
    GLuint quadVAO = createQuadVAO();
    //GLuint polygonShader = loadShaders("shaders/polygon/vert.glsl", "shaders/polygon/frag.glsl");
    GLuint screenShader = loadShaders("shaders/screen/vert.glsl", "shaders/screen/frag.glsl");
    //Object thing;
    //thing.setSpin(vec3(1.0f, 0.0f, 0.0f), 0.003f);
    PolygonArray polygonArray("objects/icosahedron.obj");
    polygonArray.addPolygon(vec3(0.0f), 1.0f);
    polygonArray.setSpin(0, vec3(0.001f, 0.001234f, 0.0f));
    polygonArray.addPolygon(vec3(2.0f, 0.0f, 0.0f), 0.5f);

    LightArray lights;
    lights.addPolygon(vec3(1.0f, 0.0f, 0.0f), 5.5f, vec3(1.0f, 0.0f, 0.0f));

    mat4 Projection = glm::perspective(
		1.2f,
		static_cast<float>(16) / 9,
		0.1f,
		100.0f
	);
    mat4 View, VP;
    
	while (!glfwWindowShouldClose(window) && !closed) {
        cam->move();
        //thing.move();
        polygonArray.move();
        lights.move();
        View = cam->getView();
        VP = Projection * View;
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer.buffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //render(icosahedron, polygonShader, 60, thing.getModel(), VP);
        polygonArray.render(VP);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //illuminateScene(quadVAO, gBuffer, screenShader);
        lights.render(gBuffer, VP);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "loadOBJ.h"
#include "loadshaders.h"
#include "matrix.h"

using namespace glm;

struct Polygon {
    float size;
    vec3 pos, vel, spinVector;
    mat3 Rotation, Spin;
};

class PolygonArray {
public:
    PolygonArray() {}
	PolygonArray(const char* objPath);
    void addPolygon(vec3 pos, float size);
	void render(mat4 VP);
	void move();
    void setSpin(int polygonIndex, vec3 spinVector);
	GLuint shader, vertexArray;
	float size;
    vector<Polygon*> polygons;
    vector<mat4> Models;
};
#include "polygon.h"
#include "loadOBJ.h"


PolygonArray::PolygonArray(const char* objPath) {
    shader = loadShaders("shaders/polygon/vert.glsl", "shaders/polygon/frag.glsl");
    vertexArray = loadObject(objPath);
}

void PolygonArray::addPolygon(vec3 pos, float size) {
    Polygon *p = new Polygon();
	p->pos = pos;
    p->size = size;
	p->Spin = p->Rotation = mat3(1.0f);
    p->vel = vec3(0.0f);
    polygons.push_back(p);
    Models.push_back(mat4(1.0f));
}

void PolygonArray::setSpin(int polygonIndex, vec3 spinVector) {
    polygons[polygonIndex]->spinVector = spinVector;
    polygons[polygonIndex]->Spin = srotate(spinVector);
}

void PolygonArray::move() {
    int i = 0;
	for (auto p : polygons) {
        p->pos += p->vel;
	    p->Rotation = p->Spin * p->Rotation;
	    //Model = translateR(Rotation, pos) * Scale;
	    Models[i] = translateR(p->size * p->Rotation, p->pos);
        i++;
    }
}

void PolygonArray::render(mat4 VP) {
    glBindVertexArray(vertexArray);
	glUseProgram(shader);
    glEnable(GL_DEPTH_TEST);
	glUniformMatrix4fv(glGetUniformLocation(shader, "VP"), 1, GL_FALSE, &VP[0][0]);    
	glUniformMatrix4fv(glGetUniformLocation(shader, "Model"), polygons.size(), GL_FALSE, &Models[0][0][0]);
	GLint size = 0;
	//this gets size in bytes
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	//6 float attributes per vertex
	glDrawArraysInstanced(GL_TRIANGLES, 0, size / (6 * sizeof(float)), polygons.size());	
}

/*
bool Polygon::detectCollision(Polygon& p) {
	return (length(pos - p.pos) < size + p.size);
}

void Polygon::collide(Polygon& p) {
	if (!detectCollision(p)) return;
	pos -= vel;
	p.pos -= p.vel;

	vec3 poc = pos + size * (p.pos - pos) / length(p.pos - pos);
	vec3 r1 = poc - pos;
	vec3 r2 = poc - p.pos;
	vec3 totalVelThis = vel + cross(spin, r1);
	vec3 totalVelThat = p.vel + cross(p.spin, r2);
	vec3 dv = totalVelThat - totalVelThis;
	if (dot(r1, dv) > 0) return;

	float m1 = 2 * p.size / (size + p.size);
	float m2 = 2 * size / (size + p.size);
	totalVelThis += m1 * dv;
	totalVelThat -= m2 * dv;

	float dp1 = dot(totalVelThis, r1);
	vel = dp1 * r1 / dot(r1, r1);
	float dp2 = dot(totalVelThat, r2);
	p.vel = dp2 * r2 / dot(r2, r2);

	vec3 tangentThis = totalVelThis - vel;
	setSpin(cross(tangentThis, r1) / dot(r1, r1));
	vec3 tangentThat = totalVelThat - p.vel;
	p.setSpin(cross(tangentThat, r2) / dot(r2, r2));
}

void Polygon::gravitate(Polygon& p) {
	const float G = 0.0000001;
	vec3 d = p.pos - pos;
	
	vec3 s1 = 100.0f * cross(spin, d);
	vec3 s2 = 100.0f * cross(p.spin, d);
	vel += G * p.size * (d - s2) / dot(d, d);
	p.vel -= G * size * (d + s1) / dot(d, d);
}

void Polygon::render(GLuint VAO) {
	
}

void Polygon::setViewProjection(mat4 VP) {
	glUseProgram(program);
	GLuint l_M = glGetUniformLocation(program, "VP");
	glUniformMatrix4fv(l_M, 1, GL_FALSE, &VP[0][0]);
}

void Polygon::setCameraPosition(vec3 p) {
	glUseProgram(program);
	GLuint l_p = glGetUniformLocation(program, "cPos");
	glUniform3fv(l_p, 1, &p[0]);
}

void Polygon::setSpin(vec3 _spin) {
	spin = _spin;
	Spin = srotate(_spin);
}
*/
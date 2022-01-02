#pragma once

#include "polygon.h"
#include "gbuffer.h"

class LightArray : public PolygonArray {
public:
    LightArray();
    void addPolygon(vec3 pos, float size, vec3 color);
    void render(GBuffer gBuffer, mat4 VP);
    vector<vec3> colors;
};
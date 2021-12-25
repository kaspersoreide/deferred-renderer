#pragma once
/* gBuffer code. The gBuffer is a framebuffer with 3 color attachments (positions, normals, color).
 * all coordinates are in world space */ 

#include <GL/glew.h>

struct GBuffer {
    GLuint buffer, gPosition, gNormal, gColor, depthBuffer;
    GBuffer();
};

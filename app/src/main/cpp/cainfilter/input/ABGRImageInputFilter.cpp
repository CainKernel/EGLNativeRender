//
// Created by admin on 2018/4/4.
//

#include "ABGRImageInputFilter.h"

ABGRImageInputFilter::ABGRImageInputFilter() {
    ABGRImageInputFilter(getVertexShader(), getFragmentShader());
}

ABGRImageInputFilter::ABGRImageInputFilter(const char *vertexShader, const char *fragmentShader)
        : GLImageInputFilter(vertexShader, fragmentShader) {}

ShaderType ABGRImageInputFilter::getShaderType(void) {
    return FRAGMENT_ABGR;
}

bool ABGRImageInputFilter::drawFrame(void *bufY, void *bufU, void *bufV) {
    return GLImageInputFilter::drawFrame(bufY, bufU, bufV);
}

bool ABGRImageInputFilter::drawFrame(void *bufY, void *bufU, void *bufV, GLfloat *vertices,
                                     GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrame(bufY, bufU, bufV, vertices, textureCoords);
}


int ABGRImageInputFilter::drawFrameBuffer(void *bufY, void *bufU, void *bufV, GLfloat *vertices,
                                          GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrameBuffer(bufY, bufU, bufV, vertices, textureCoords);
}

int ABGRImageInputFilter::drawFrameBuffer(void *bufY, void *bufU, void *bufV) {
    return GLImageInputFilter::drawFrameBuffer(bufY, bufU, bufV);
}

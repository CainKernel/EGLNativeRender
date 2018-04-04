//
// Created by admin on 2018/4/4.
//

#include "ARGBImageInputfilter.h"

ARGBImageInputfilter::ARGBImageInputfilter() {
    ARGBImageInputfilter(getVertexShader(), getFragmentShader());
}

ARGBImageInputfilter::ARGBImageInputfilter(const char *vertexShader, const char *fragmentShader)
        : GLImageInputFilter(vertexShader, fragmentShader) {
}

ShaderType ARGBImageInputfilter::getShaderType(void) {
    return FRAGMENT_ARGB;
}

bool ARGBImageInputfilter::drawFrame(void *bufY, void *bufU, void *bufV) {
    return GLImageInputFilter::drawFrame(bufY, bufU, bufV);
}

bool ARGBImageInputfilter::drawFrame(void *bufY, void *bufU, void *bufV, GLfloat *vertices,
                                     GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrame(bufY, bufU, bufV, vertices, textureCoords);
}


int ARGBImageInputfilter::drawFrameBuffer(void *bufY, void *bufU, void *bufV, GLfloat *vertices,
                                          GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrameBuffer(bufY, bufU, bufV, vertices, textureCoords);
}

int ARGBImageInputfilter::drawFrameBuffer(void *bufY, void *bufU, void *bufV) {
    return GLImageInputFilter::drawFrameBuffer(bufY, bufU, bufV);
}


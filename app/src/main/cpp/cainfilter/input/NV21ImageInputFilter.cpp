//
// Created by admin on 2018/4/4.
//

#include "NV21ImageInputFilter.h"

NV21ImageInputFilter::NV21ImageInputFilter() {
    NV21ImageInputFilter(getVertexShader(), getFragmentShader());
}

NV21ImageInputFilter::NV21ImageInputFilter(const char *vertexShader, const char *fragmentShader)
        : GLImageInputFilter(vertexShader, fragmentShader) {}

ShaderType NV21ImageInputFilter::getShaderType(void) {
    return FRAGMENT_NV21;
}

bool NV21ImageInputFilter::drawFrame(void *bufRGB) {
    return GLImageInputFilter::drawFrame(bufRGB);
}

bool NV21ImageInputFilter::drawFrame(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrame(bufRGB, vertices, textureCoords);
}

int NV21ImageInputFilter::drawFrameBuffer(void *bufRGB) {
    return GLImageInputFilter::drawFrameBuffer(bufRGB);
}

int NV21ImageInputFilter::drawFrameBuffer(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrameBuffer(bufRGB, vertices, textureCoords);
}



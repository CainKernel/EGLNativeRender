//
// Created by admin on 2018/4/4.
//

#include "NV12ImageInputFilter.h"

NV12ImageInputFilter::NV12ImageInputFilter() {}

NV12ImageInputFilter::NV12ImageInputFilter(const char *vertexShader, const char *fragmentShader)
        : GLImageInputFilter(vertexShader, fragmentShader) {}

ShaderType NV12ImageInputFilter::getShaderType(void) {
    return FRAGMENT_NV12;
}

bool NV12ImageInputFilter::drawFrame(void *bufRGB) {
    return GLImageInputFilter::drawFrame(bufRGB);
}

bool NV12ImageInputFilter::drawFrame(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrame(bufRGB, vertices, textureCoords);
}

int NV12ImageInputFilter::drawFrameBuffer(void *bufRGB) {
    return GLImageInputFilter::drawFrameBuffer(bufRGB);
}

int NV12ImageInputFilter::drawFrameBuffer(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrameBuffer(bufRGB, vertices, textureCoords);
}

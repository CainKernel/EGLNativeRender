//
// Created by admin on 2018/4/4.
//

#include "I420ImageInputFilter.h"

I420ImageInputFilter::I420ImageInputFilter() {
    I420ImageInputFilter(getVertexShader(), getFragmentShader());
}

I420ImageInputFilter::I420ImageInputFilter(const char *vertexShader, const char *fragmentShader)
        : GLImageInputFilter(vertexShader, fragmentShader) {
}

ShaderType I420ImageInputFilter::getShaderType(void) {
    return FRAGMENT_I420;
}

bool I420ImageInputFilter::drawFrame(void *bufRGB) {
    return GLImageInputFilter::drawFrame(bufRGB);
}

bool I420ImageInputFilter::drawFrame(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrame(bufRGB, vertices, textureCoords);
}

int I420ImageInputFilter::drawFrameBuffer(void *bufRGB) {
    return GLImageInputFilter::drawFrameBuffer(bufRGB);
}

int
I420ImageInputFilter::drawFrameBuffer(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrameBuffer(bufRGB, vertices, textureCoords);
}



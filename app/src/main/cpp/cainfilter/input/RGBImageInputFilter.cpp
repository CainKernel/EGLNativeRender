//
// Created by admin on 2018/4/4.
//

#include "RGBImageInputFilter.h"
RGBImageInputFilter::RGBImageInputFilter() {
    RGBImageInputFilter(getVertexShader(), getFragmentShader());
}

RGBImageInputFilter::RGBImageInputFilter(const char *vertexShader, const char *fragmentShader)
        : GLImageInputFilter(vertexShader, fragmentShader) {
}


ShaderType RGBImageInputFilter::getShaderType(void) {
    return FRAGMENT_RGB;
}

bool RGBImageInputFilter::drawFrame(void *bufY, void *bufU, void *bufV) {
    return GLImageInputFilter::drawFrame(bufY, bufU, bufV);
}

bool RGBImageInputFilter::drawFrame(void *bufY, void *bufU, void *bufV, GLfloat *vertices,
                                    GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrame(bufY, bufU, bufV, vertices, textureCoords);
}

int RGBImageInputFilter::drawFrameBuffer(void *bufY, void *bufU, void *bufV, GLfloat *vertices,
                                         GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrameBuffer(bufY, bufU, bufV, vertices, textureCoords);
}

int RGBImageInputFilter::drawFrameBuffer(void *bufY, void *bufU, void *bufV) {
    return GLImageInputFilter::drawFrameBuffer(bufY, bufU, bufV);
}






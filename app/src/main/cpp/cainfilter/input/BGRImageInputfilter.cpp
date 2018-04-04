//
// Created by admin on 2018/4/4.
//

#include "BGRImageInputfilter.h"

BGRImageInputfilter::BGRImageInputfilter() {
    BGRImageInputfilter(getVertexShader(), getFragmentShader());
}

BGRImageInputfilter::BGRImageInputfilter(const char *vertexShader, const char *fragmentShader)
        : GLImageInputFilter(vertexShader, fragmentShader) {
}

ShaderType BGRImageInputfilter::getShaderType(void) {
    return FRAGMENT_BGR;
}

bool BGRImageInputfilter::drawFrame(void *bufY, void *bufU, void *bufV) {
    return GLImageInputFilter::drawFrame(bufY, bufU, bufV);
}

bool BGRImageInputfilter::drawFrame(void *bufY, void *bufU, void *bufV, GLfloat *vertices,
                                    GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrame(bufY, bufU, bufV, vertices, textureCoords);
}

int BGRImageInputfilter::drawFrameBuffer(void *bufY, void *bufU, void *bufV) {
    return GLImageInputFilter::drawFrameBuffer(bufY, bufU, bufV);
}

int BGRImageInputfilter::drawFrameBuffer(void *bufY, void *bufU, void *bufV, GLfloat *vertices,
                                         GLfloat *textureCoords) {
    return GLImageInputFilter::drawFrameBuffer(bufY, bufU, bufV, vertices, textureCoords);
}

//
// Created by admin on 2018/4/4.
//

#ifndef EGLNATIVESAMPLE_ARGBIMAGEINPUTFILTER_H
#define EGLNATIVESAMPLE_ARGBIMAGEINPUTFILTER_H


#include "../GLImageInputFilter.h"

class ARGBImageInputfilter : public GLImageInputFilter {

public:
    ARGBImageInputfilter();

    ARGBImageInputfilter(const char *vertexShader, const char *fragmentShader);

protected:
    virtual ShaderType getShaderType(void);

private:
    virtual bool drawFrame(void *bufY, void *bufU, void *bufV);

    virtual bool drawFrame(void *bufY, void *bufU, void *bufV, GLfloat *vertices, GLfloat *textureCoords);

    virtual int drawFrameBuffer(void *bufY, void *bufU, void *bufV);

    virtual int drawFrameBuffer(void *bufY, void *bufU, void *bufV, GLfloat *vertices, GLfloat *textureCoords);
};


#endif //EGLNATIVESAMPLE_ARGBIMAGEINPUTFILTER_H

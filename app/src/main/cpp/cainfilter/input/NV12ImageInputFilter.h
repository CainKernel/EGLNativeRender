//
// Created by admin on 2018/4/4.
//

#ifndef EGLNATIVESAMPLE_NV12IMAGEINPUTFILTER_H
#define EGLNATIVESAMPLE_NV12IMAGEINPUTFILTER_H


#include "../GLImageInputFilter.h"

class NV12ImageInputFilter : public GLImageInputFilter {
public:
    NV12ImageInputFilter();

    NV12ImageInputFilter(const char *vertexShader, const char *fragmentShader);

protected:
    virtual ShaderType getShaderType(void);

private:
    virtual bool drawFrame(void *bufRGB);

    virtual bool drawFrame(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords);

    virtual int drawFrameBuffer(void *bufRGB);

    virtual int drawFrameBuffer(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords);
};


#endif //EGLNATIVESAMPLE_NV12IMAGEINPUTFILTER_H

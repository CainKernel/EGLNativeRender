//
// Created by admin on 2018/4/4.
//

#ifndef EGLNATIVESAMPLE_YUV420PIMAGEINPUTFILTER_H
#define EGLNATIVESAMPLE_YUV420PIMAGEINPUTFILTER_H


#include "../GLImageInputFilter.h"

class I420ImageInputFilter : public GLImageInputFilter {
protected:
public:
    I420ImageInputFilter();

    I420ImageInputFilter(const char *vertexShader, const char *fragmentShader);

protected:
    virtual ShaderType getShaderType(void);

private:
    virtual bool drawFrame(void *bufRGB);

    virtual bool drawFrame(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords);

    virtual int drawFrameBuffer(void *bufRGB);

    virtual int drawFrameBuffer(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords);
};


#endif //EGLNATIVESAMPLE_YUV420PIMAGEINPUTFILTER_H

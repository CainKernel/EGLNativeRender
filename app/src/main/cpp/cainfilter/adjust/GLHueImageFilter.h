//
// Created by admin on 2018/4/4.
//

#ifndef EGLNATIVESAMPLE_GLHUEIMAGEFILTER_H
#define EGLNATIVESAMPLE_GLHUEIMAGEFILTER_H


#include "../GLImageFilter.h"

class GLHueImageFilter : public GLImageFilter {
public:
    GLHueImageFilter();

    GLHueImageFilter(const char *vertexShader, const char *fragmentShader);

    inline void setHue(int hue) {
        this->hue = hue;
    }

protected:
    virtual void initHandle(void);

    virtual void bindValue(GLint texture, GLfloat *vertices, GLfloat *textureCoords);

    virtual const char *getFragmentShader(void);

private:
    int mHueLoc;
    int hue;
};


#endif //EGLNATIVESAMPLE_GLHUEIMAGEFILTER_H

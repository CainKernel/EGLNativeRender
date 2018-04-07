//
// Created by admin on 2018/4/3.
//

#ifndef EGLNATIVESAMPLE_GLRENDER_H
#define EGLNATIVESAMPLE_GLRENDER_H


#include <android/native_window.h>
#include "../caingles/EglCore.h"
#include "../caingles/WindowSurface.h"
#include "Triangle.h"

class GLRender {
public:
    GLRender();

    virtual ~GLRender();

    void surfaceCreated(ANativeWindow *window);

    void surfaceChanged(int width, int height);

    void surfaceDestroyed(void);

private:
    EglCore *mEglCore;
    WindowSurface *mWindowSurface;
    Triangle *mTriangle;
};


#endif //EGLNATIVESAMPLE_GLRENDER_H

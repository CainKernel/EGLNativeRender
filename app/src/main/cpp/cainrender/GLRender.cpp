//
// Created by admin on 2018/4/3.
//

#include "GLRender.h"
#include "../caingles/GlUtils.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <assert.h>

GLRender::GLRender() {
    mEglCore = NULL;
    mWindowSurface = NULL;
}

GLRender::~GLRender() {
    if (mEglCore) {
        mEglCore->release();
        delete mEglCore;
        mEglCore = NULL;
    }
}

void GLRender::surfaceCreated(ANativeWindow *window) {

    if (mEglCore == NULL) {
        mEglCore = new EglCore(NULL, FLAG_RECORDABLE);
    }
    mWindowSurface = new WindowSurface(mEglCore, window, false);
    assert(mWindowSurface != NULL && mEglCore != NULL);
    mWindowSurface->makeCurrent();
    mTriangle = new Triangle();
    mTriangle->init();
}

void GLRender::surfaceChanged(int width, int height) {
    mWindowSurface->makeCurrent();
    mTriangle->onDraw(width, height);
    mWindowSurface->swapBuffers();
}

void GLRender::surfaceDestroyed() {
    if (mTriangle) {
        mTriangle->destroy();
        delete mTriangle;
        mTriangle = NULL;
    }
    if (mWindowSurface) {
        mWindowSurface->release();
        delete mWindowSurface;
        mWindowSurface = NULL;
    }
    if (mEglCore) {
        mEglCore->release();
        delete mEglCore;
        mEglCore = NULL;
    }
}

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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glDisable(GL_DEPTH_TEST);
    mWindowSurface->swapBuffers();
}

void GLRender::surfaceChanged(int width, int height) {

}

void GLRender::surfaceDestroyed() {
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

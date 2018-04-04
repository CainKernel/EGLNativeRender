//
// Created by admin on 2018/4/3.
//

#ifndef EGLNATIVESAMPLE_MYLOOPER_H
#define EGLNATIVESAMPLE_MYLOOPER_H

#include "Looper.h"
#include "../cainrender/GLRender.h"

enum {
    kMsgSurfaceCreated,
    kMsgSurfaceChanged,
    kMsgSurfaceDestroyed
};

class MyLooper : public Looper {

public:
    MyLooper();

    virtual ~MyLooper();

    virtual void handleMessage(LooperMessage *msg);

private:
    GLRender *mRender;

};


#endif //EGLNATIVESAMPLE_MYLOOPER_H

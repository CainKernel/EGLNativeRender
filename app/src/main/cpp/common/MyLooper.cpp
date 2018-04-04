//
// Created by admin on 2018/4/3.
//

#include "MyLooper.h"

MyLooper::MyLooper() {
    mRender = new GLRender();
}

void MyLooper::handleMessage(LooperMessage *msg) {
    switch (msg && msg->what) {
        case kMsgSurfaceCreated:
            if (mRender) {
                mRender->surfaceCreated((ANativeWindow *) msg->obj);
            }
            break;

        case kMsgSurfaceChanged:
            if (mRender) {
                mRender->surfaceChanged(msg->arg1, msg->arg2);
            }
            break;

        case kMsgSurfaceDestroyed:
            if (mRender) {
                mRender->surfaceDestroyed();
            }
            break;
    }
}

MyLooper::~MyLooper() {
    delete mRender;
}




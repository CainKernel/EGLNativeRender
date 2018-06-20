package com.cgfay.eglnativerender;

import android.view.Surface;

public class EGLRender {
    static {
        System.loadLibrary("nativeEgl");
    }
    private native void nativeInit();
    private native void nativeRelease();
    private native void onSurfaceCreated(Surface surface);
    private native void onSurfaceChanged(int width, int height);
    private native void onSurfaceDestroyed();

    public EGLRender() {
    }

    public void init() {
        nativeInit();
    }

    public void release() {
        nativeRelease();
    }

    public void surfaceCreated(Surface surface) {
        onSurfaceCreated(surface);
    }

    public void surfaceChanged(int width, int height) {
        onSurfaceChanged(width, height);
    }

    public void surfaceDestroyed() {
        onSurfaceDestroyed();
    }
}

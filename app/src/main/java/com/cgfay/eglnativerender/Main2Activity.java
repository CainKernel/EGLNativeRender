package com.cgfay.eglnativerender;

import android.annotation.SuppressLint;
import android.graphics.SurfaceTexture;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Gravity;
import android.view.Surface;
import android.view.TextureView;
import android.widget.FrameLayout;

import javax.microedition.khronos.egl.EGL;

public class Main2Activity extends AppCompatActivity implements TextureView.SurfaceTextureListener {

    private static final int MSG_RENDER_FRAME = 0x01;
    private TextureView mTextureView;
    private EGLRender mRender;
    private Surface mSurface;
    private FrameLayout mFrameLayout;

    private Handler mHandler = new MainHandler();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        mFrameLayout = (FrameLayout) findViewById(R.id.frameLayout);
        mRender = new EGLRender();
        mRender.init();
        mTextureView = new TextureView(this);
        mTextureView.setSurfaceTextureListener(this);
        mFrameLayout.addView(mTextureView);
    }

    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        mTextureView.setLayoutParams(
                new FrameLayout.LayoutParams(1080, 1920, Gravity.CENTER));
        surface.setDefaultBufferSize(1080, 1920);
        mSurface = new Surface(surface);
        mRender.surfaceCreated(mSurface);
        mRender.surfaceChanged(1080, 1920);
    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, final int width, final int height) {

    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        mRender.surfaceDestroyed();
        return false;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {

    }

    @SuppressLint("HandlerLeak")
    class MainHandler extends Handler {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case MSG_RENDER_FRAME:
                    mRender.surfaceChanged(msg.arg1, msg.arg2);
                    mHandler.sendMessageDelayed(mHandler.obtainMessage(MSG_RENDER_FRAME, msg.arg1, msg.arg2), 100);
                    break;
            }
        }
    }

}

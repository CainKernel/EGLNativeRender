package com.cgfay.eglnativerender;

import android.graphics.SurfaceTexture;
import android.opengl.GLES30;
import android.os.Handler;
import android.os.HandlerThread;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.cgfay.eglnativerender.filter.OESInputFilter;
import com.cgfay.eglnativerender.gles.EglCore;
import com.cgfay.eglnativerender.gles.WindowSurface;
import com.cgfay.eglnativerender.utils.GlUtil;

public class Main3Activity extends AppCompatActivity implements SurfaceHolder.Callback,
        SurfaceTexture.OnFrameAvailableListener {

    private static final String TAG = "Render";

    private SurfaceView mSurfaceView;

    private EGLRender mRender;

    private Handler mRenderHandler;
    private HandlerThread mRenderThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mRender = new EGLRender();
        mRender.init();
        mSurfaceView = (SurfaceView) findViewById(R.id.surface_view);
        mSurfaceView.getHolder().addCallback(this);
    }

    @Override
    protected void onDestroy() {
        mRender.release();
        mRender = null;
        super.onDestroy();
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        initRenderThread();
        internalSurfaceCreated(holder);

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        internalSurfaceChanged(width, height);

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        internalSurfaceDestroyed();
    }

    @Override
    public void onFrameAvailable(SurfaceTexture surfaceTexture) {
        requestRender();
    }

    /**
     * 初始化渲染线程
     */
    private void initRenderThread() {
        mRenderThread = new HandlerThread("RenderThread");
        mRenderThread.start();
        mRenderHandler = new Handler(mRenderThread.getLooper());
    }

    /**
     * 创建Surface
     */
    private void internalSurfaceCreated(final SurfaceHolder holder) {
        mRenderHandler.post(new Runnable() {
            @Override
            public void run() {
                onSurfaceCreated(holder);
            }
        });
    }

    /**
     * Surface改变
     * @param width
     * @param height
     */
    private void internalSurfaceChanged(final int width, final int height) {
        mRenderHandler.post(new Runnable() {
            @Override
            public void run() {
                onSurfaceChanged(width, height);
            }
        });
    }

    /**
     * 销毁Surface
     */
    private void internalSurfaceDestroyed() {
        mRenderHandler.post(new Runnable() {
            @Override
            public void run() {
                onSurfaceDestroyed();
            }
        });
    }

    /**
     * 请求渲染
     */
    private void requestRender() {
        Log.d(TAG, "requestRender: ");
        mRenderHandler.post(new Runnable() {
            @Override
            public void run() {
                
                onDrawFrame();
            }
        });
    }

    // ------------------ 渲染过程 --------------------------------------------------

    private EglCore mEglCore;
    private WindowSurface mDisplaySurface;
    private int mInputTextureId;
    private SurfaceTexture mSurfaceTexture;
    private Surface mSurface;

    // 矩阵
    private final float[] mMatrix = new float[16];
    private OESInputFilter mOESInputFilter;

    private void onSurfaceCreated(SurfaceHolder holder) {
        mEglCore = new EglCore(null, EglCore.FLAG_RECORDABLE);
        mDisplaySurface = new WindowSurface(mEglCore, holder.getSurface(), false);
        mDisplaySurface.makeCurrent();
        mOESInputFilter = new OESInputFilter(Main3Activity.this);
        mOESInputFilter.onInputSizeChanged(1080, 1920);
        mOESInputFilter.onDisplayChanged(1080, 1920);

        mInputTextureId = GlUtil.createTextureOES();
        mSurfaceTexture = new SurfaceTexture(mInputTextureId);
        mSurfaceTexture.setDefaultBufferSize(1090, 1920);
        mSurfaceTexture.setOnFrameAvailableListener(this);
        mSurface = new Surface(mSurfaceTexture);
        mRender.surfaceCreated(mSurface);
    }

    private void onSurfaceChanged(int width, int height) {
        mOESInputFilter.updateTextureBuffer();
        mRender.surfaceChanged(width, height);
    }

    private void onSurfaceDestroyed() {
        if (mOESInputFilter != null) {
            mOESInputFilter.release();
            mOESInputFilter = null;
        }
        if (mSurfaceTexture != null) {
            mSurfaceTexture.release();
            mSurfaceTexture = null;
        }

        if (mDisplaySurface != null) {
            mDisplaySurface.release();
            mDisplaySurface = null;
        }

        if (mEglCore != null) {
            mEglCore.release();
            mEglCore = null;
        }

        mRender.surfaceDestroyed();
    }

    private void onDrawFrame() {
        if (mSurfaceTexture == null) {
            return;
        }
        mSurfaceTexture.updateTexImage();
        mDisplaySurface.makeCurrent();
        mSurfaceTexture.getTransformMatrix(mMatrix);
        if (mOESInputFilter != null) {
            mOESInputFilter.setTextureTransformMatirx(mMatrix);
            // 绘制渲染
            GLES30.glViewport(0, 0, 1080, 1920);
            mOESInputFilter.drawFrame(mInputTextureId);
        }
        mDisplaySurface.swapBuffers();
    }
}

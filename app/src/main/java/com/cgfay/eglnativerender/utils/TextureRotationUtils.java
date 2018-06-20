package com.cgfay.eglnativerender.utils;

import android.hardware.Camera;

import java.nio.FloatBuffer;

/**
 * Created by cain on 17-7-26.
 */

public class TextureRotationUtils {

    // 摄像头是否倒置，主要是应对Nexus 5X (bullhead) 的后置摄像头图像倒置的问题
    private static boolean mBackReverse = false;

    public static final int CoordsPerVertex = 3;

    public static final float CubeVertices[] = {
            -1.0f, -1.0f, 0.0f,  // 0 bottom left
            1.0f, -1.0f,  0.0f,  // 1 bottom right
            -1.0f,  1.0f, 0.0f,  // 2 top left
            1.0f,  1.0f,  0.0f,  // 3 top right
    };

    public static final float TextureVertices[] = {
            0.0f, 0.0f,     // 0 bottom left
            1.0f, 0.0f,     // 1 bottom right
            0.0f, 1.0f,     // 2 top left
            1.0f, 1.0f      // 3 top right
    };

    public static final float TextureVertices_90[] = {
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
    };

    public static final float TextureVertices_180[] = {
            1.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
    };

    public static final float TextureVertices_270[] = {
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
    };

    public static float[] getTextureVertices() {
        return TextureVertices;
    }

    public static FloatBuffer getTextureBuffer() {
        return GlUtil.createFloatBuffer(TextureRotationUtils.TextureVertices);
    }

    public static void setBackReverse(boolean reverse) {
        mBackReverse = reverse;
    }
}

package com.cgfay.eglnativerender.filter;

import android.content.Context;

/**
 * 预览的滤镜
 * Created by cain.huang on 2017/9/29.
 */
public class DisplayFilter extends BaseImageFilter {

    public DisplayFilter(Context context) {
        this(context, VERTEX_SHADER, FRAGMENT_SHADER_2D);
    }

    public DisplayFilter(Context context, String vertexShader, String fragmentShader) {
        super(context, vertexShader, fragmentShader);
    }
}

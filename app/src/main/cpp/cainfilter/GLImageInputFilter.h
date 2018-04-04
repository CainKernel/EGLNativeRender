//
// Created by admin on 2018/4/4.
//

#ifndef EGLNATIVESAMPLE_GLIMAGEINPUTFILTER_H
#define EGLNATIVESAMPLE_GLIMAGEINPUTFILTER_H

#include "../caingles/GlUtils.h"

class GLImageInputFilter {

public:
    GLImageInputFilter();
    GLImageInputFilter(const char *vertexShader, const char *fragmentShader);
    virtual ~GLImageInputFilter();
    // 输入大小发生变化
    virtual void onInputSizeChanged(int width, int height);
    // 界面大小发生变化
    virtual void onDisplayChanged(int width, int height);
    // 绘制RGB图像数据
    virtual bool drawFrame(void *bufRGB);
    // 绘制RGB图像数据
    virtual bool drawFrame(void *bufRGB, GLfloat vertices[], GLfloat textureCoords[]);
    // 绘制YUV图像数据
    virtual bool drawFrame(void *bufY, void *bufU, void *bufV);
    // 绘制YUV图像数据
    virtual bool drawFrame(void *bufY, void *bufU, void *bufV, GLfloat vertices[], GLfloat textureCoords[]);
    // 将RGB图像数据绘制到FBO
    virtual int drawFrameBuffer(void *bufRGB);
    // 将RGB图像数据绘制到FBO
    virtual int drawFrameBuffer(void *bufRGB, GLfloat vertices[], GLfloat textureCoords[]);
    // 将YUV图像数据绘制到FBO
    virtual int drawFrameBuffer(void *bufY, void *bufU, void *bufV);
    // 将YUV图像数据绘制到FBO
    virtual int drawFrameBuffer(void *bufY, void *bufU, void *bufV, GLfloat vertices[], GLfloat textureCoords[]);
    // 设置总变换
    void setMVPMatrix(ESMatrix *matrix);
    // 初始化FBO
    virtual void initFrameBuffer(int width, int height);
    // 销毁FBO
    virtual void destroyFrameBuffer();

protected:
    // 加载 vertex shader
    virtual const char *getVertexShader(void);
    // 加载 fragment shader
    virtual const char *getFragmentShader(void);
    // 设置单位矩阵
    void initIdentityMatrix();
    // 初始化句柄
    virtual void initHandle(void);
    // 句柄
    virtual void viewport();
    // 初始化Texture
    virtual void initTexture(int width, int height);
    // 释放资源
    virtual void release(void);
    // 初始化坐标
    virtual void initCoordinates();
    // 获取输入类型
    virtual ShaderType getShaderType(void);
    // 顶点坐标
    GLfloat vertexCoordinates[8] = {0};
    // 纹理坐标
    GLfloat textureCoordinates[8] = {0};
    // 句柄
    GLint programHandle;
    GLint mvpMatrixHandle;
    GLint positionHandle;
    GLint textureCoordsHandle;
    GLint inputTextureHandle[3] = {0};

    // 矩阵对象
    ESMatrix *mvpMatrix;
    // yuv的Texture
    GLuint mTextureId[3];

    // 输入宽度
    int videoWidth;
    // 输入高度
    int videoHeight;
    // Surface的宽度
    int screenWidth;
    // Surface的高度
    int screenHeight;
    // 实际显示的宽度
    int viewWidth;
    // 实际显示的高度
    int viewHeight;

    // FBO
    GLuint mFrameBuffers[1];
    GLuint mFrameBufferTextures[1];
    int mFrameWidth;
    int mFrameHeight;
};


#endif //EGLNATIVESAMPLE_GLIMAGEINPUTFILTER_H

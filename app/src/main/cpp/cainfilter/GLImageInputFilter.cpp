//
// Created by admin on 2018/4/4.
//

#include "GLImageInputFilter.h"

GLImageInputFilter::GLImageInputFilter() {
    GLImageInputFilter(getVertexShader(), getFragmentShader());
}

GLImageInputFilter::GLImageInputFilter(const char *vertexShader, const char *fragmentShader) {
    programHandle = createProgram(vertexShader, fragmentShader);
    initHandle();
    initIdentityMatrix();
    initCoordinates();
}

GLImageInputFilter::~GLImageInputFilter() {
    release();
}

/**
 * 输入大小发生变化
 * @param width
 * @param height
 */
void GLImageInputFilter::onInputSizeChanged(int width, int height) {
    videoWidth = width;
    videoHeight = height;
    initTexture(width, height);
}

/**
 * 初始化Texture
 * @param width
 * @param height
 */
void GLImageInputFilter::initTexture(int width, int height) {
    glGenTextures(1, &mTextureId[0]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width, height, 0,
                 GL_LUMINANCE, GL_UNSIGNED_BYTE, NULL);
    glUniform1i(inputTextureHandle[0], 0);

    glGenTextures(1, &mTextureId[1]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTextureId[1]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width/2, height/2, 0,
                 GL_LUMINANCE, GL_UNSIGNED_BYTE, NULL);
    glUniform1i(inputTextureHandle[1], 1);


    glGenTextures(1, &mTextureId[2]);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mTextureId[2]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, width/2, height/2, 0,
                 GL_LUMINANCE, GL_UNSIGNED_BYTE, NULL);
    glUniform1i(inputTextureHandle[2], 2);
}

/**
 * 显示发生改变
 * @param width
 * @param height
 */
void GLImageInputFilter::onDisplayChanged(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    // 重新计算屏幕位置
    viewport();
}

/**
 * 绘制RGB
 * @param bufRGB
 * @return
 */
bool GLImageInputFilter::drawFrame(void *bufRGB) {
    drawFrame(bufRGB, vertexCoordinates, textureCoordinates);
}

/**
 * 绘制RGB
 * @param bufRGB
 * @param vertices
 * @param textureCoords
 * @return
 */
bool GLImageInputFilter::drawFrame(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords) {
    if (programHandle < 0 || bufRGB == NULL) {
        return false;
    }
    glUseProgram(programHandle);

    glVertexAttribPointer(positionHandle, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionHandle);

    glVertexAttribPointer(textureCoordsHandle, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);
    glEnableVertexAttribArray(textureCoordsHandle);

    glUniform4fv(mvpMatrixHandle, 1, mvpMatrix->m);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId[0]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, videoWidth, videoHeight,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, bufRGB);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(positionHandle);
    glDisableVertexAttribArray(textureCoordsHandle);
    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgram(0);
    return true;
}

/**
 * 绘制yuv
 * @param bufY
 * @param bufU
 * @param bufV
 * @return
 */
bool GLImageInputFilter::drawFrame(void *bufY, void *bufU, void *bufV) {
    return drawFrame(bufY, bufU, bufV, vertexCoordinates, textureCoordinates);
}

/**
 * 绘制YUV
 * @param bufY
 * @param bufU
 * @param bufV
 * @param vertices
 * @param textureCoords
 * @return
 */
bool GLImageInputFilter::drawFrame(void *bufY, void *bufU, void *bufV, GLfloat vertices[],
                                   GLfloat textureCoords[]) {

    if (programHandle < 0 || bufY == NULL || bufU == NULL || bufV == NULL) {
        return false;
    }
    glUseProgram(programHandle);

    glVertexAttribPointer(positionHandle, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionHandle);

    glVertexAttribPointer(textureCoordsHandle, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);
    glEnableVertexAttribArray(textureCoordsHandle);

    glUniform4fv(mvpMatrixHandle, 1, mvpMatrix->m);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId[0]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, videoWidth, videoHeight,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, bufY);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTextureId[1]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, videoWidth / 2, videoWidth / 2,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, bufU);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mTextureId[2]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, videoWidth / 2, videoWidth / 2,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, bufV);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(positionHandle);
    glDisableVertexAttribArray(textureCoordsHandle);
    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgram(0);
    return true;
}

/**
 * 将RGB绘制到FBO
 * @param bufRGB
 * @return
 */
int GLImageInputFilter::drawFrameBuffer(void *bufRGB) {
    drawFrameBuffer(bufRGB, vertexCoordinates, textureCoordinates);
}

/**
 * 将RGB图像数据绘制到FBO
 * @param bufRGB
 * @param vertices
 * @param textureCoords
 * @return
 */
int GLImageInputFilter::drawFrameBuffer(void *bufRGB, GLfloat *vertices, GLfloat *textureCoords) {
    if (mFrameBuffers[0] == GL_NONE) {
        return GL_NONE;
    }
    glViewport(0, 0, mFrameWidth, mFrameHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffers[0]);
    glUseProgram(programHandle);

    glVertexAttribPointer(positionHandle, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionHandle);

    glVertexAttribPointer(textureCoordsHandle, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);
    glEnableVertexAttribArray(textureCoordsHandle);

    glUniform4fv(mvpMatrixHandle, 1, mvpMatrix->m);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId[0]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, videoWidth, videoHeight,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, bufRGB);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(positionHandle);
    glDisableVertexAttribArray(textureCoordsHandle);
    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgram(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return mFrameBufferTextures[0];
}

/**
 * 将YUV图像数据绘制到FBO
 * @param bufY
 * @param bufU
 * @param bufV
 * @return
 */
int GLImageInputFilter::drawFrameBuffer(void *bufY, void *bufU, void *bufV) {
    return drawFrameBuffer(bufY, bufU, bufV, vertexCoordinates, textureCoordinates);
}

/**
 * 将YUV图像数据绘制到FBO
 * @param bufY
 * @param bufU
 * @param bufV
 * @param vertices
 * @param textureCoords
 * @return
 */
int GLImageInputFilter::drawFrameBuffer(void *bufY, void *bufU, void *bufV, GLfloat *vertices,
                                        GLfloat *textureCoords) {
    if (mFrameBuffers[0] == GL_NONE) {
        return GL_NONE;
    }
    glViewport(0, 0, mFrameWidth, mFrameHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffers[0]);
    glUseProgram(programHandle);

    glVertexAttribPointer(positionHandle, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionHandle);

    glVertexAttribPointer(textureCoordsHandle, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);
    glEnableVertexAttribArray(textureCoordsHandle);

    glUniform4fv(mvpMatrixHandle, 1, mvpMatrix->m);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId[0]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, videoWidth, videoHeight,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, bufY);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTextureId[1]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, videoWidth / 2, videoWidth / 2,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, bufU);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mTextureId[2]);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, videoWidth / 2, videoWidth / 2,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, bufV);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(positionHandle);
    glDisableVertexAttribArray(textureCoordsHandle);
    glBindTexture(GL_TEXTURE_2D, 0);

    glUseProgram(0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return mFrameBufferTextures[0];
}

/**
 * 计算viewport
 */
void GLImageInputFilter::viewport() {
    int left,top;
    if (screenHeight > screenWidth) {
        left = 0;
        viewWidth = screenWidth;
        viewHeight = (int)(videoHeight * 1.0f / videoWidth * viewWidth);
        top = (screenHeight - viewHeight) / 2;
    } else {
        top = 0;
        viewHeight = screenHeight;
        viewWidth = (int)(videoWidth * 1.0f / videoHeight * viewHeight);
        left = (screenWidth - viewWidth) / 2;
    }
    glViewport(left, top, viewWidth, viewHeight);
}

/**
 * 初始化单位矩阵
 */
void GLImageInputFilter::initIdentityMatrix() {
    setIdentityM(mvpMatrix);
}

/**
 * 设置MVP矩阵
 * @param matrix
 */
void GLImageInputFilter::setMVPMatrix(ESMatrix *matrix) {
    ESMatrix *temp = mvpMatrix;
    mvpMatrix = matrix;
    free(temp);
}

/**
 * 初始化句柄
 */
void GLImageInputFilter::initHandle(void) {
    if (programHandle == GL_NONE) {
        ALOGE("program is empty!");
        return;
    }
    positionHandle = glGetAttribLocation(programHandle, "aPosition");
    textureCoordsHandle = glGetAttribLocation(programHandle, "aTextureCoord");
    mvpMatrixHandle = glGetAttribLocation(programHandle, "uMVPMatrix");
    // YUV渲染
    if (getShaderType() == FRAGMENT_I420 || getShaderType() == FRAGMENT_NV12
        || getShaderType() == FRAGMENT_NV21) {
        inputTextureHandle[0] = glGetUniformLocation(programHandle, "inputTextureY");
        inputTextureHandle[1] = glGetUniformLocation(programHandle, "inputTextureU");
        inputTextureHandle[2] = glGetUniformLocation(programHandle, "inputTextureV");
    } else if (getShaderType() == FRAGMENT_ABGR || getShaderType() == FRAGMENT_ARGB
               || getShaderType() == FRAGMENT_BGR || getShaderType() == FRAGMENT_RGB) {
        inputTextureHandle[0] = glGetAttribLocation(programHandle, "inputTexture");
    } else {
        ALOGE("unsupport shader type!");
    }
}

// 释放资源
void GLImageInputFilter::release(void) {
    if (programHandle >= 0) {
        glDeleteProgram(programHandle);
        programHandle = -1;
    }
    if (mvpMatrix) {
        free(mvpMatrix);
        mvpMatrix = NULL;
    }
    // 删除Texture
    glDeleteTextures(3, mTextureId);
}

// 初始化坐标
void GLImageInputFilter::initCoordinates() {
// 初始化顶点坐标
    // 0 bottom left
    vertexCoordinates[0] = -1.0f;
    vertexCoordinates[1] = -1.0f;
    // 1 bottom right
    vertexCoordinates[2] = 1.0f;
    vertexCoordinates[3] = -1.0f;
    // 2 top left
    vertexCoordinates[4] = -1.0f;
    vertexCoordinates[5] = 1.0f;
    // 3 top right
    vertexCoordinates[6] = 1.0f;
    vertexCoordinates[7] = 1.0f;

    // 初始化纹理坐标
    // 0 bottom left
    textureCoordinates[0] = 0.0f;
    textureCoordinates[1] = 0.0f;
    // 1 bottom right
    textureCoordinates[2] = 1.0f;
    textureCoordinates[3] = 0.0f;
    // 2 top left
    textureCoordinates[4] = 0.0f;
    textureCoordinates[5] = 1.0f;
    // 3 top right
    textureCoordinates[6] = 1.0f;
    textureCoordinates[7] = 1.0f;
}

/**
 * 初始化FBO
 * @param width
 * @param height
 */
void GLImageInputFilter::initFrameBuffer(int width, int height) {
    if (mFrameBuffers[0] != GL_NONE && (mFrameWidth != width || mFrameHeight != height)) {
        destroyFrameBuffer();
    }
    if (mFrameBuffers[0] == GL_NONE) {
        mFrameWidth = width;
        mFrameHeight = height;
        createFrameBuffer(mFrameBuffers, mFrameBufferTextures, width, height);
    }
}

/**
 * 销毁FBO
 */
void GLImageInputFilter::destroyFrameBuffer() {
    if (mFrameBufferTextures[0] != GL_NONE) {
        glDeleteTextures(1, mFrameBufferTextures);
        mFrameBufferTextures[0] = GL_NONE;
    }
    if (mFrameBuffers[0] != GL_NONE) {
        glDeleteFramebuffers(1, mFrameBuffers);
        mFrameBuffers[0] = GL_NONE;
    }
    mFrameWidth = -1;
    mFrameHeight = -1;
}

const char* GLImageInputFilter::getVertexShader() {
    return GlShader_GetShader(VERTEX_REVERSE);
}

const char* GLImageInputFilter::getFragmentShader() {
    return GlShader_GetShader(getShaderType());
}

ShaderType GLImageInputFilter::getShaderType() {
    return FRAGMENT_RGB;
}
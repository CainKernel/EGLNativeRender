//
// Created by cain on 2018/4/7.
//

#include "Triangle.h"

const GLint COORDS_PER_VERTEX = 3;
const GLint vertexStride = COORDS_PER_VERTEX * 4;

Triangle::Triangle() {}

Triangle::~Triangle() {

}

int Triangle::init() {
    char vertexShader[] =
            "#version 300 es\n"
                    "layout(location = 0) in vec4 a_position;\n"
                    "layout(location = 1) in vec4 a_color;\n"
                    "out vec4 v_color;"
                    "void main()\n"
                    "{\n"
                    "   gl_Position = a_position;\n"
                    "   v_color = a_color;\n"
                    "}\n";

    char fragmentShader[] =
            "#version 300 es\n"
                    "precision mediump float;\n"
                    "in vec4 v_color;\n"
                    "out vec4 fragColor;\n"
                    "void main()\n"
                    "{\n"
//                    "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );\n"
                    "   fragColor = v_color;\n"
                    "}\n";
    programHandle = createProgram(vertexShader, fragmentShader);
    if (programHandle <= 0) {
        return -1;
    }
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    return 0;
}


void Triangle::onDraw(int width, int height) {
    ALOGD("hahahah");
    GLfloat vertices[] = {
            0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };

    GLfloat color[] = {
            1.0f, 0.0f, 0.0f, 1.0f
    };

    GLint vertexCount = sizeof(vertices) / (sizeof(vertices[0]) * COORDS_PER_VERTEX);

    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programHandle);

    GLint positionHandle = glGetAttribLocation(programHandle, "a_position");
    glVertexAttribPointer(positionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE, vertexStride, vertices);
    glEnableVertexAttribArray(positionHandle);
    glVertexAttrib4fv(1, color);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glDisableVertexAttribArray(positionHandle);
}

void Triangle::destroy() {
    if (programHandle > 0) {
        glDeleteProgram(programHandle);
    }
    programHandle = -1;
}
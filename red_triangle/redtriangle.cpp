#include "redtriangle.h"
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QOpenGLFunctions>
#include <QSurface>

RedTriangle::RedTriangle()
    :mVBO(QOpenGLBuffer::VertexBuffer)
{
    this->resize(600,400);
}

void RedTriangle::initializeGL()
{
    //vertexes data
    const float vertexes[] = {
        -1.0f,-1.0f,0.0f,
        1.0f,-1.0f,0.0f,
        0.0f,1.0f,0.0f
    };
    GLWindow::initializeGL();
    this->mShaderProgram = compileShader(":/red_triangle/shader.vert",":/red_triangle/shader.frag");
    Q_ASSERT(this->mShaderProgram);
    this->mShaderProgram->bind();
    this->mVertexPositionName = this->mShaderProgram->attributeLocation("VertexPosition");

    Q_ASSERT(mVAO.create());
    mVAO.bind();
    Q_ASSERT(mVBO.create());
    mVBO.bind();
    mVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mVBO.allocate(vertexes, sizeof(vertexes));

    mVBO.write(0,vertexes,sizeof(vertexes));
    this->mShaderProgram->enableAttributeArray(this->mVertexPositionName);
    this->mShaderProgram->setAttributeBuffer(this->mVertexPositionName,GL_FLOAT,0,3,0);
    //TODO : cannot disable here , why?
    //this->mShaderProgram->disableAttributeArray(this->mVertexPositionName);
    this->mShaderProgram->release();

    mVBO.release();
    mVAO.release();
    glClearColor(0,0,0,1);
}

void RedTriangle::paintGL()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    this->mShaderProgram->bind();
    this->mShaderProgram->enableAttributeArray(this->mVertexPositionName);
    this->mVAO.bind();
    this->mVBO.bind();
    glDrawArrays(GL_TRIANGLES,0,3);
    this->mVBO.release();
    this->mVAO.release();
    this->mShaderProgram->disableAttributeArray(this->mVertexPositionName);
    this->mShaderProgram->release();
}

RedTriangle::~RedTriangle()
{
    //TODO : Need destroy manually?
    if(mVBO.isCreated())
        mVBO.destroy();
    if(mVAO.isCreated())
        mVAO.destroy();
}





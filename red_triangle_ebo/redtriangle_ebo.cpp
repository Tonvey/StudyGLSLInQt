#include "redtriangle_ebo.h"
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QOpenGLFunctions>
#include <QSurface>

RedTriangleEBO::RedTriangleEBO()
    :mVBO(QOpenGLBuffer::VertexBuffer)
    ,mEBO(QOpenGLBuffer::IndexBuffer)
{
    this->resize(600,400);
}

void RedTriangleEBO::initializeGL()
{
    //vertexes data
    const float vertexes[] = {
        -1.0f,-1.0f,0.0f,
        1.0f,-1.0f,0.0f,
        0.0f,1.0f,0.0f
    };
    //indices data
    const GLuint indices[] = {
        0,1,2
    };
    GLWindow::initializeGL();
    this->mShaderProgram = compileShader(":/red_triangle_ebo/shader.vert",":/red_triangle_ebo/shader.frag");
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
    Q_ASSERT(mEBO.create());
    mEBO.bind();
    mEBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mEBO.allocate(indices, sizeof(indices));
    mEBO.write(0,indices,sizeof(indices));

    this->mShaderProgram->enableAttributeArray(this->mVertexPositionName);
    this->mShaderProgram->setAttributeBuffer(this->mVertexPositionName,GL_FLOAT,0,3,0);
    //TODO : cannot disable here , why?
    //this->mShaderProgram->disableAttributeArray(this->mVertexPositionName);
    this->mShaderProgram->release();

    mEBO.release();
    mVBO.release();
    mVAO.release();
    glClearColor(0,0,0,1);
}

void RedTriangleEBO::paintGL()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    this->mShaderProgram->bind();
    this->mShaderProgram->enableAttributeArray(this->mVertexPositionName);
    this->mVAO.bind();
    this->mVBO.bind();
    this->mEBO.bind();
    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)0);
    this->mEBO.release();
    this->mVBO.release();
    this->mVAO.release();
    this->mShaderProgram->disableAttributeArray(this->mVertexPositionName);
    this->mShaderProgram->release();
}

RedTriangleEBO::~RedTriangleEBO()
{
    //TODO : Need destroy manually?
    if(mVBO.isCreated())
        mVBO.destroy();
    if(mEBO.isCreated())
        mEBO.destroy();
    if(mVAO.isCreated())
        mVAO.destroy();
}





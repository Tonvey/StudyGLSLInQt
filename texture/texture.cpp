#include "texture.h"
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QOpenGLFunctions>
#include <QSurface>
#include <QDebug>

Texture::Texture()
    :mVBO(QOpenGLBuffer::VertexBuffer)
    ,mUV(QOpenGLBuffer::VertexBuffer)
    ,mEBO(QOpenGLBuffer::IndexBuffer)
{
    this->resize(600,400);
}
void Texture::initializeGL()
{
    //vertexes data
    const float vertexes[] = {
        0.5f, 0.5f, -1.0f,   // 右上角
        0.5f, -0.5f, -1.0f,  // 右下角
        -0.5f, -0.5f, -1.0f, // 左下角
        -0.5f, 0.5f, -1.0f   // 左上角
    };
    const GLfloat uvBuffer[] = {
        1.0,1.0,
        1.0,0.0,
        0.0,0.0,
        0.0,1.0,
    };
    //indices data
    const GLuint indices[] = {
        // 起始于0!
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
    GLWindow::initializeGL();
    this->makeCurrent();
    this->mShaderProgram = compileShader(":/texture/shader.vert",":/texture/shader.frag");
    Q_ASSERT(this->mShaderProgram);
    this->mShaderProgram->bind();
    this->mVertexPositionName = this->mShaderProgram->attributeLocation("VertexPosition");
    this->mVertexUVCoordName = this->mShaderProgram->attributeLocation("uv");
    this->mTextureName = this->mShaderProgram->uniformLocation("MyTexture");

    //vao
    Q_ASSERT(mVAO.create());
    mVAO.bind();

    //vbo
    Q_ASSERT(mVBO.create());
    mVBO.bind();
    mVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mVBO.allocate(vertexes, sizeof(vertexes));
    mVBO.write(0,vertexes,sizeof(vertexes));

    this->mShaderProgram->enableAttributeArray(this->mVertexPositionName);
    this->mShaderProgram->setAttributeBuffer(this->mVertexPositionName,GL_FLOAT,0,3,0);

    //uvbo
    Q_ASSERT(mUV.create());
    mUV.bind();
    mUV.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mUV.allocate(uvBuffer, sizeof(uvBuffer));
    mUV.write(0,uvBuffer,sizeof(uvBuffer));

    this->mShaderProgram->enableAttributeArray(this->mVertexUVCoordName);
    this->mShaderProgram->setAttributeBuffer(this->mVertexUVCoordName,GL_FLOAT,0,2,0);

    //ebo
    Q_ASSERT(mEBO.create());
    mEBO.bind();
    mEBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mEBO.allocate(indices, sizeof(indices));
    mEBO.write(0,indices,sizeof(indices));

    mVBO.release();
    mUV.release();
    mEBO.release();

    //texture bo
    mTBO = new QOpenGLTexture(QImage(":/texture/panda.bmp").mirrored());
    mTBO->setMinificationFilter(QOpenGLTexture::Nearest);
    mTBO->setMagnificationFilter(QOpenGLTexture::Linear);
    mTBO->setWrapMode(QOpenGLTexture::ClampToEdge);
    mTBO->bind();

    mTBO->release();
    mVAO.release();
    this->mShaderProgram->release();
}
void Texture::paintGL()
{
    glClearColor(0, 0, 0.3, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    this->mShaderProgram->bind();
    this->mVAO.bind();
    this->mVBO.bind();
    this->mUV.bind();
    this->mEBO.bind();
    //this->mShaderProgram->setUniformValue(this->mTextureName,0);
    this->mTBO->bind();
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,(void*)0);
    this->mTBO->release();
    this->mEBO.release();
    this->mUV.release();
    this->mVBO.release();
    this->mVAO.release();
    this->mShaderProgram->release();
}
Texture::~Texture()
{
    if(mTBO)
        delete mTBO;
}

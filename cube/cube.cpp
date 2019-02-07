#include "cube.h"
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QOpenGLFunctions>
#include <QSurface>
#include <QDebug>

//vertexes data
static const float vertexes[] = {
    -0.5f, 0.5f, 0.0f,   // 前左上角
    0.5f, 0.5f, 0.0f,    // 前右上角
    0.5f, -0.5f, 0.0f,   // 前右下角
    -0.5f, -0.5f, 0.0f,  // 前左下角

    -0.5f, 0.5f, -1.0f,  // 后左上角
    0.5f, 0.5f, -1.0f,   // 后右上角
    0.5f, -0.5f, -1.0f,  // 后右下角
    -0.5f, -0.5f, -1.0f, // 后左下角
};

//indices data
static const GLuint indices[] = {
    //前
    0,2,1,
    0,3,2,
    //右
    2,5,1,
    2,6,5,
    //后
    5,6,7,
    5,7,4,
    //左
    4,7,0,
    7,3,0,
    //顶
    0,1,5,
    0,5,4,
    //底
    3,6,2,
    3,7,6,
};
static const GLfloat uvBuffer[] = {
    0.0,1.0,
    1.0,1.0,
    1.0,0.0,
    0.0,0.0,
    0.0,1.0,
    1.0,1.0,
    1.0,0.0,
    0.0,0.0,
};
Cube::Cube()
        :mVBO(QOpenGLBuffer::VertexBuffer)
        ,mUV(QOpenGLBuffer::VertexBuffer)
        ,mEBO(QOpenGLBuffer::IndexBuffer)
{
    this->resize(600,400);
}
void Cube::initializeGL()
{
    GLWindow::initializeGL();
    this->makeCurrent();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    this->mShaderProgram = compileShader(":/cube/shader.vert",":/cube/shader.frag");
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
    glClearColor(0, 0, 0.3, 1);
}
void Cube::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    this->mShaderProgram->bind();
    this->mVAO.bind();
    this->mVBO.bind();
    this->mUV.bind();
    this->mEBO.bind();
    QMatrix4x4 mvp = this->makeMVP();
    this->mShaderProgram->setUniformValue("mvp",mvp);
    this->mTBO->bind();
    glDrawElements(GL_TRIANGLES,sizeof(indices)/sizeof(indices[0]),GL_UNSIGNED_INT,(void*)0);
    this->mTBO->release();
    this->mEBO.release();
    this->mUV.release();
    this->mVBO.release();
    this->mVAO.release();
    this->mShaderProgram->release();
}
Cube::~Cube()
{
    if(mTBO)
        delete mTBO;
}

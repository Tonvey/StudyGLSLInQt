#include "redtriangle.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QOpenGLFunctions>
#include <QSurface>

static const float sg_vertexes[] = {
    -1.0f,-1.0f,0.0f,
    1.0f,-1.0f,0.0f,
    0.0f,1.0f,0.0f
};
RedTriangle::RedTriangle(QWidget *parent)
{
    this->resize(600,400);
}

void RedTriangle::initializeGL()
{
    GLWindow::initializeGL();
    //加载shader
    QOpenGLShader vs(QOpenGLShader::Vertex ,this);
    if(!vs.compileSourceFile(":/red_triangle/shader.vert"))
    {
        qCritical()<<"Vertex shader compile error : "<<vs.log();
        this->close();
        return ;
    }

    QOpenGLShader fs(QOpenGLShader::Fragment ,this);
    if(!fs.compileSourceFile(":/red_triangle/shader.frag"))
    {
        qCritical()<<"Fragment shader compile error : "<<fs.log();
        this->close();
        return ;
    }

    this->mShaderProgram = new QOpenGLShaderProgram(this);
    this->mShaderProgram->addShader(&vs);
    this->mShaderProgram->addShader(&fs);
    if(!this->mShaderProgram->link())
    {
        qCritical()<<"Program link error : "<<this->mShaderProgram->log();
        this->close();
        return ;
    }
    this->mShaderProgram->bind();
    this->mVertexPositionName = this->mShaderProgram->attributeLocation("VertexPosition");

    mVAO.create();
    if(mVAO.isCreated())
    {
        mVAO.bind();
    }
    else
    {
        //TODO:
    }
    mVBO.create();
    if(mVBO.isCreated())
    {
        mVBO.bind();
    }
    else
    {
        //TODO:
    }
    mVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mVBO.allocate(sg_vertexes, sizeof(sg_vertexes));

    mVBO.write(0,sg_vertexes,sizeof(sg_vertexes));
    this->mShaderProgram->setAttributeBuffer(this->mVertexPositionName,GL_FLOAT,0,3,0);
    this->mShaderProgram->enableAttributeArray(this->mVertexPositionName);


    mVBO.release();
    mVAO.release();
    this->mShaderProgram->release();

    glClearColor(0,0,0,1);
}

void RedTriangle::paintGL()
{
    static int frame=0;
    qDebug()<<frame++;
    glClear(GL_COLOR_BUFFER_BIT);
    this->mShaderProgram->bind();
    this->mVAO.bind();
    //this->mShaderProgram->enableAttributeArray(this->mVertexPositionName);
    //this->mShaderProgram->setAttributeArray(this->mVertexPositionName,GL_FLOAT,0,3);
    glDrawArrays(GL_TRIANGLES,0,3);
    this->mShaderProgram->disableAttributeArray(this->mVertexPositionName);
    this->mVAO.release();
    this->mShaderProgram->release();
}

RedTriangle::~RedTriangle()
{
    if(mVBO.isCreated())
        mVBO.destroy();
    if(mVAO.isCreated())
        mVAO.destroy();
    if(this->mShaderProgram)
        delete this->mShaderProgram;
}





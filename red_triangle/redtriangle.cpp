#include "redtriangle.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <QOpenGLFunctions>

static const float sg_vertexes[] = {
    -1.0f,-1.0f,0.0f,
    1.0f,-1.0f,0.0f,
    0.0f,1.0f,0.0f
};
RedTriangle::RedTriangle(QWidget *parent) : GLBaseWidget(parent)
{
}

void RedTriangle::initializeGL()
{
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

    mVAO.create();
    if(mVAO.isCreated())
    {
        mVAO.bind();
    }

    mVBO.create();
    mVBO.bind();
    mVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mVBO.allocate(sg_vertexes, sizeof(sg_vertexes));

    this->mVertexPositionName = this->mShaderProgram->attributeLocation("VertexPosition");
    //this->mShaderProgram->setAttributeArray("VertexPosition",GL_FLOAT,sg_vertexes,3);

//    p->
//
//    //在显卡中申请内存，内存句柄是vertexbuffer
//    glGenBuffers(1,&vertexbuffer);
//    //对vertexbuffer进行操作
//    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
//    //把顶点坐标g_vertex_buffer_data传递到显卡，保存到vertexbuffer中
//    glBufferData(
//                GL_ARRAY_BUFFER,
//                sizeof(g_vertex_buffer_data),
//                g_vertex_buffer_data,
//                GL_STATIC_DRAW
    //                );
    glClearColor(0,0,0,1);
}

void RedTriangle::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);
    this->mShaderProgram->bind();
    this->mVBO.bind();
    this->mShaderProgram->enableAttributeArray(this->mVertexPositionName);
    this->mShaderProgram->setAttributeArray(this->mVertexPositionName,GL_FLOAT,0,3);
    f->glDrawArrays(GL_TRIANGLES,0,3);
    this->mShaderProgram->disableAttributeArray(this->mVertexPositionName);
    //this->mVBO.release();
    //this->mShaderProgram->release();
}





#include "glwindow.h"
#include <QDebug>
#include <QDateTime>

GLWindow::GLWindow()
    :mLastFrameTime(QDateTime::currentMSecsSinceEpoch())
{
    QSurfaceFormat format;
    format.setVersion(4,1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    this->setFormat(format);

    //synchronized to the vertical refresh
    connect(this,&GLWindow::frameSwapped,[this](){
        //update last frame time
        auto curTime = QDateTime::currentMSecsSinceEpoch();
        this->mElpase = double(curTime - mLastFrameTime)/1000;
        this->mLastFrameTime=curTime;
        this->update();
    });
}

GLWindow::~GLWindow()
{
    qDebug()<<"GLWindow closed";
}
void GLWindow::printOpenGLInfomation()
{
    qDebug()<<"OpenGL version: "<<(char*)glGetString(GL_VERSION);
    qDebug()<<"GLSL version: "<<(char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    qDebug()<<"Vendor: "<<(char*)glGetString(GL_VENDOR);
    qDebug()<<"Renderer: "<<(char*)glGetString(GL_RENDERER);
}

void GLWindow::paintGLInfo()
{

}

QOpenGLShaderProgram *GLWindow::compileShader(QString vs, QString tc, QString te, QString gs, QString fs)
{
    QOpenGLShaderProgram *p = new QOpenGLShaderProgram(this);
    if(!p->addShaderFromSourceFile(QOpenGLShader::Vertex,vs))
    {
        qCritical()<<"Vertex shader compile error : "<<p->log();
        delete p;
        return nullptr;
    }

    if(!tc.isNull()&&!tc.isEmpty())
    {
        if(!p->addShaderFromSourceFile(QOpenGLShader::TessellationControl,tc))
        {
            qCritical()<<"Tesselation Control shader compile error : "<<p->log();
            delete p;
            return nullptr;
        }
    }
    if(!te.isNull()&&!te.isEmpty())
    {
        if(!p->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation,te))
        {
            qCritical()<<"Tesselation Evaluation shader compile error : "<<p->log();
            delete p;
            return nullptr;
        }
    }
    if(!te.isNull()&&!te.isEmpty())
    {
        if(!p->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation,te))
        {
            qCritical()<<"Tesselation Evaluation shader compile error : "<<p->log();
            delete p;
            return nullptr;
        }
    }
    if(!gs.isNull()&&!te.isEmpty())
    {
        if(!p->addShaderFromSourceFile(QOpenGLShader::Geometry,gs))
        {
            qCritical()<<"Geometry shader compile error : "<<p->log();
            delete p;
            return nullptr;
        }
    }
    if(!p->addShaderFromSourceFile(QOpenGLShader::Fragment,fs))
    {
        qCritical()<<"Fragment shader compile error : "<<p->log();
        delete p;
        return nullptr;
    }

    if(!p->link())
    {
        qCritical()<<"Program link error : "<<p->log();
        delete p;
        return nullptr;
    }
    return p;
}

QOpenGLShaderProgram *GLWindow::compileShader(QString vs, QString fs)
{
    return compileShader(vs,QString(),QString(),QString(),fs);
}
void GLWindow::initializeGL()
{
    this->printOpenGLInfomation();
}

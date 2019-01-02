#include "glbasewidget.h"
#include <QOpenGLContext>
#include <QDebug>
#include <gl.h>

GLBaseWidget::GLBaseWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setVersion(4,1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    this->setFormat(format); // must be called before the widget or its parent window gets shown
}
void GLBaseWidget::printOpenGLInfomation()
{
    //qDebug()<<"OpenGL version"<<this->format().majorVersion()<<"."<<this->format().minorVersion();
    qDebug()<<"OpenGL version: "<<(char*)glGetString(GL_VERSION);
    qDebug()<<"GLSL version: "<<(char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    qDebug()<<"Vendor: "<<(char*)glGetString(GL_VENDOR);
    qDebug()<<"Renderer: "<<(char*)glGetString(GL_RENDERER);
}

void GLBaseWidget::initializeGL()
{
    this->printOpenGLInfomation();
}

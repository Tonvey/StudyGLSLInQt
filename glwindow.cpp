#include "glwindow.h"
#include <QDebug>
#include <QDateTime>
#include <QKeyEvent>
#include <QMouseEvent>
#include <cmath>

const double PI = atan(1.)*4;

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
        this->mElapse = double(curTime - mLastFrameTime)/1000;
        this->mLastFrameTime=curTime;
        this->update();
    });

    //Use blank cursor for gl window
    this->setCursor(Qt::BlankCursor);

    memset(&mControlState,0,sizeof(mControlState));
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

void GLWindow::resetCursorToCenter()
{
    QPoint p(this->size().width()/2,this->size().height()/2);
    p = this->mapToGlobal(p);
    QCursor::setPos(p);
}

void GLWindow::mouseMoveEvent(QMouseEvent *e)
{
    QPoint center(this->size().width()/2,this->size().height()/2);
    QPoint p = e->pos();
    QPoint diff = p-center;
    this->mControlState.verticalAngle -= diff.y()*0.001*PI;
    if(mControlState.verticalAngle>PI/2)
    {
        mControlState.verticalAngle=PI/2;
    }
    if(mControlState.verticalAngle<-PI/2)
    {
        mControlState.verticalAngle=-PI/2;
    }
    this->mControlState.horizontalAngle -= diff.x()*0.001*PI;

    QOpenGLWindow::mouseMoveEvent(e);
    this->resetCursorToCenter();
}

void GLWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_W:
        this->mControlState.forward=true;
        break;
    case Qt::Key_S:
        this->mControlState.backward=true;
        break;
    case Qt::Key_A:
        this->mControlState.left=true;
        break;
    case Qt::Key_D:
        this->mControlState.right=true;
        break;
    case Qt::Key_Escape:
        //TODO:complete the close logic
        break;
    }

    if(e->modifiers()&Qt::ShiftModifier)
    {
        this->mControlState.up=true;
    }
    else if(e->modifiers()&Qt::ControlModifier)
    {
        this->mControlState.down=true;
    }
}

void GLWindow::resizeEvent(QResizeEvent *event)
{
    //when resize window ,shoud reset cursor to window center
    this->resetCursorToCenter();
    QOpenGLWindow::resizeEvent(event);
}

void GLWindow::paintGLInfo()
{

}

QMatrix4x4 GLWindow::makeMVP()
{
    QMatrix4x4 mvp;
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;
    double movement = this->mElapse*10;
    //Direction : Spherical coordinates to Cartesian coordinates conversion
    mEyeDirction.setX(cos(mControlState.verticalAngle)*sin(mControlState.horizontalAngle));
    mEyeDirction.setY(sin(mControlState.verticalAngle));
    mEyeDirction.setZ(cos(mControlState.verticalAngle)*cos(mControlState.horizontalAngle));

    QVector3D rightVec;
    rightVec.setX(sin(mControlState.horizontalAngle-PI/2));
    rightVec.setY(0);
    rightVec.setZ(cos(mControlState.horizontalAngle-PI/2));

    mEyeUpVec = QVector3D::crossProduct(rightVec,mEyeDirction);

    if(this->mControlState.forward)
    {
        mEyePos += mEyeDirction*movement;
        mControlState.forward=false;
    }
    if(this->mControlState.backward)
    {
        mEyePos -= mEyeDirction*movement;
        mControlState.backward=false;
    }
    if(this->mControlState.left)
    {
        mEyePos -= rightVec*movement;
        mControlState.left=false;
    }
    if(this->mControlState.right)
    {
        mEyePos += rightVec*movement;
        mControlState.right=false;
    }
    if(this->mControlState.up)
    {
        mEyePos += mEyeUpVec*movement;
        mControlState.up=false;
    }
    if(this->mControlState.down)
    {
        mEyePos -= mEyeUpVec*movement;
        mControlState.down=false;
    }
    projection.perspective(45,1.0*this->size().width()/this->size().height(),0.3,100.0);
    view.lookAt(this->mEyePos,this->mEyePos+this->mEyeDirction,this->mEyeUpVec);
    mvp = projection * view * model;
    return mvp;
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

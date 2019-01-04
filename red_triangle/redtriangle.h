#ifndef REDTRIANGLE_H
#define REDTRIANGLE_H

#include <QWidget>
//#include "glbasewidget.h"
#include "glwindow.h"
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class RedTriangle : public GLWindow
{
    Q_OBJECT
public:
    RedTriangle(QWidget *parent = nullptr);
    virtual void initializeGL()override;
    virtual void paintGL()override;
    ~RedTriangle();

signals:

public slots:
private:
    QOpenGLShaderProgram *mShaderProgram;
    QOpenGLBuffer mVBO;
    QOpenGLVertexArrayObject mVAO;
    GLuint mVertexPositionName;
};

#endif // REDTRIANGLE_H

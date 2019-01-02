#ifndef REDTRIANGLE_H
#define REDTRIANGLE_H

#include <QWidget>
#include "glbasewidget.h"
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_4_1_Core>

class RedTriangle : public GLBaseWidget
{
    Q_OBJECT
public:
    explicit RedTriangle(QWidget *parent = nullptr);
    virtual void initializeGL()override;
    virtual void paintGL()override;

signals:

public slots:
private:
    QOpenGLShaderProgram *mShaderProgram;
    QOpenGLBuffer mVBO;
    QOpenGLVertexArrayObject mVAO;
    GLuint mVertexPositionName;
};

#endif // REDTRIANGLE_H

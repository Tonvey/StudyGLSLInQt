#ifndef REDTRIANGLE_EBO_H
#define REDTRIANGLE_EBO_H

#include <QWidget>
#include "glwindow.h"
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class RedTriangleEBO : public GLWindow
{
    Q_OBJECT
public:
    RedTriangleEBO();
    virtual void initializeGL()override;
    virtual void paintGL()override;
    ~RedTriangleEBO();

signals:

public slots:
private:
    QOpenGLShaderProgram *mShaderProgram;
    QOpenGLBuffer mVBO;
    QOpenGLBuffer mEBO;
    QOpenGLVertexArrayObject mVAO;
    GLuint mVertexPositionName;
};

#endif // REDTRIANGLE_EBO_H

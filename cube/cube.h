#ifndef CUBE_H
#define CUBE_H

#include <QWidget>
#include "glwindow.h"
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

class Cube  : public GLWindow
{
    Q_OBJECT
public:
    Cube();
    virtual void initializeGL()override;
    virtual void paintGL()override;
    ~Cube();

signals:

public slots:
private:
    QOpenGLShaderProgram *mShaderProgram;
    QOpenGLBuffer mVBO;
    QOpenGLBuffer mUV;
    QOpenGLBuffer mEBO;
    QOpenGLTexture *mTBO;
    QOpenGLVertexArrayObject mVAO;
    GLuint mVertexPositionName;
    GLuint mVertexUVCoordName;
    GLuint mTextureName;
};

#endif // CUBE_H

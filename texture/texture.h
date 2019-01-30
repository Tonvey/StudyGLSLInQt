#ifndef TEXTURE_H
#define TEXTURE_H

#include <QWidget>
#include "glwindow.h"
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>

class Texture  : public GLWindow
{
    Q_OBJECT
public:
    Texture();
    virtual void initializeGL()override;
    virtual void paintGL()override;
    ~Texture();

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

#endif // TEXTURE_H

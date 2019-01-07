#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLShaderProgram>

class GLWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    GLWindow();
    ~GLWindow();
    void initializeGL()override;
    void printOpenGLInfomation();
private:
protected:
    virtual void paintGLInfo();
    //Compile vertex,tesselation control,tesslation evaluation,geometry and fragment shader
    //return program object in success , otherwise return nullptr
    QOpenGLShaderProgram *compileShader(
            QString vs,
            QString tc,
            QString te,
            QString gs,
            QString fs);
    //wrapper
    QOpenGLShaderProgram *compileShader( QString vs, QString fs);


    //render information member
    qint64 mLastFrameTime; //millseconds from the day
    double mElpase; 		//elpase(second) between last two frame
};

#endif

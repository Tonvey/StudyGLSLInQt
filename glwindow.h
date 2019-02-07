#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class GLWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    GLWindow();
    ~GLWindow();
    void initializeGL()override;
    void printOpenGLInfomation();
    void resetCursorToCenter();
private:
protected:
    struct ControlStat
    {
        bool forward:1;
        bool backward:1;
        bool left:1;
        bool right:1;
        bool up:1;
        bool down:1;
        double verticalAngle;
        double horizontalAngle;
    }mControlState;
    virtual void mouseMoveEvent(QMouseEvent *)override;
    virtual void keyPressEvent(QKeyEvent *)override;
    virtual void resizeEvent(QResizeEvent *event)override;
    QVector3D mEyePos;
    QVector3D mEyeDirction;
    QVector3D mEyeUpVec;
    virtual void paintGLInfo();
    virtual QMatrix4x4 makeMVP();
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
    double mElapse; 		//elapse(second) between last two frame
};

#endif

#ifndef GLBASEWIDGET_H
#define GLBASEWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>

class GLBaseWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLBaseWidget(QWidget *parent = nullptr);
    virtual void initializeGL()override;
    void printOpenGLInfomation();
signals:

public slots:
};

#endif // GLBASEWIDGET_H

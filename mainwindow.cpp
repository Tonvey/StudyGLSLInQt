#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <functional>
#include "red_triangle/redtriangle.h"
#include "red_triangle_ebo/redtriangle_ebo.h"
#include "texture/texture.h"
#include "cube/cube.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800,600);
    this->mEntryList.append(EntryPoint("RedTriangle","Red triangle sample",[](){return (GLWindow*)(new RedTriangle);}));
    this->mEntryList.append(EntryPoint("RedTriangleEBO","Red triangle sample use ebo",[](){return (GLWindow*)(new RedTriangleEBO);}));
    this->mEntryList.append(EntryPoint("Texture","Texture sample",[](){return (GLWindow*)(new Texture);}));
    this->mEntryList.append(EntryPoint("Cube","Cube sample",[](){return (GLWindow*)(new Cube);}));
    for(auto it = this->mEntryList.begin();it!=mEntryList.end();++it)
    {
        QPushButton *btn = new QPushButton(it->title(),this);
        this->ui->verticalLayout_center->insertWidget(this->ui->verticalLayout_center->count()-1, btn);
        connect(btn,&QPushButton::clicked,[=](){it->show();});
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

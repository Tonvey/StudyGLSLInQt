#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "red_triangle/redtriangle.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->mEntryList.append(EntryPoint("RedTriangle","Red triangle sample",[](){return (GLBaseWidget*)(new RedTriangle);}));
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

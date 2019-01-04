#include "entrypoint.h"

EntryPoint::EntryPoint(QString title, QString description,GLWidgetFatctoryFn fn)
    :mTitle(title)
    ,mDescription(description)
    ,mFactoryFn(fn)
{
}

void EntryPoint::show()
{
    GLWindow *wid = mFactoryFn();
    wid->show();
    QObject::connect(wid,&GLWindow::visibleChanged,[=](bool isVisible){
        if(!isVisible)
        {
            wid->close();
            wid->deleteLater();
        }
    });
}

QString EntryPoint::title() const
{
    return mTitle;
}

void EntryPoint::setTitle(const QString &title)
{
    mTitle = title;
}

QString EntryPoint::description() const
{
    return mDescription;
}

void EntryPoint::setDescription(const QString &description)
{
    mDescription = description;
}


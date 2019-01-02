#include "entrypoint.h"

EntryPoint::EntryPoint(QString title, QString description,GLWidgetFatctoryFn fn)
    :mTitle(title)
    ,mDescription(description)
    ,mFactoryFn(fn)
{
}

void EntryPoint::show()
{
    GLBaseWidget *wid = mFactoryFn();
    wid->setAttribute(Qt::WA_DeleteOnClose);
    wid->show();
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


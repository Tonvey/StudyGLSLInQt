#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <functional>
#include <QString>
#include "glbasewidget.h"

class EntryPoint
{
public:
    typedef GLBaseWidget *(*GLWidgetFatctoryFn)();
    EntryPoint(QString title, QString description,GLWidgetFatctoryFn fn);
    void show();
    QString title() const;
    void setTitle(const QString &title);

    QString description() const;
    void setDescription(const QString &description);

private:
    QString mTitle;
    QString mDescription;
    GLWidgetFatctoryFn mFactoryFn;
};

#endif // ENTRYPOINT_H

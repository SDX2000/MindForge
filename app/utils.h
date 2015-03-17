#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QString>
#include <QRect>
#include <QWidget>

template <typename T>
void safe_delete(T *&ptr)
{
    delete ptr;
    ptr = NULL;
}

template <typename T>
T max(T t, T u)
{
    return t > u? t: u;
}


template <typename T>
T min(T t, T u)
{
    return t > u? t: u;
}

QString readAllText(QString filePath);

QRect mapToParent(QWidget *widget, QRect r);

#define QDBG        qDebug().nospace()
#define SHOW(X)     #X "=" << (X) <<", "
#define TRACE(X)    QDBG << #X "=" << (X);

#endif // COMMON_H


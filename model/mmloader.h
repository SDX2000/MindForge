#ifndef MMMODEL_H
#define MMMODEL_H

#include "mmnode.h"

#include <QDir>
#include <QString>
#include <exception>

class BadFile: public std::exception
{
    QString m_message;
public:

    BadFile(QString filePath)
      : m_message(filePath)
    {

    }

    virtual const char* what() const
    {
        return m_message.toUtf8().constData();
    }

    QString message() const
    {
        return m_message;
    }
};

class MmLoader
{
public:
    static MmNode load(QDir baseDir);
};

#endif // MMMODEL_H

#ifndef MMMODEL_H
#define MMMODEL_H

#include "mmnode.h"

#include <QDir>
#include <QString>
#include <exception>

class BadFile: public std::exception
{
    QString m_message;
    QByteArray m_baMessage;
public:

    BadFile(QString filePath)
      : m_message(filePath)
      , m_baMessage(filePath.toUtf8())
    {

    }

    virtual const char* what() const
    {
        return m_baMessage.constData();
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

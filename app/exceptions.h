#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <QString>

class BadFile: public std::exception
{
    QString m_message;
    QByteArray m_baMessage;
public:
    BadFile(QString filePath);
    virtual const char* what() const;
    QString message() const;
};

#endif // EXCEPTIONS_H

#include "exceptions.h"


BadFile::BadFile(QString filePath)
  : m_message(filePath)
  , m_baMessage(filePath.toUtf8())
{

}

const char* BadFile::what() const
{
    return m_baMessage.constData();
}

QString BadFile::message() const
{
    return m_message;
}


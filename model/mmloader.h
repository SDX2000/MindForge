#ifndef MMMODEL_H
#define MMMODEL_H

#include "mmnode.h"

#include <QDir>
#include <QString>

class MmLoader
{
public:
    static MmNode load(QDir baseDir);
};

#endif // MMMODEL_H

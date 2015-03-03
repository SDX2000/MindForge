#ifndef MMLOADER_H
#define MMLOADER_H

#include "mmnode.h"

#include <QString>



class MmLoader
{
public:
    static MmNode Load(QString fileName);
};

#endif // MMLOADER_H

#include <QApplication>

#include "promind.h"
#include "mmwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("SDXTECH");
    QCoreApplication::setOrganizationDomain("sdxtech.net");
    QCoreApplication::setApplicationName("ProMind");

    ProMind w;
    w.show();
    return a.exec();
}

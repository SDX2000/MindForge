#include <QApplication>

#include "promindwindow.h"
#include "mmwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("SDXTECH");
    QCoreApplication::setOrganizationDomain("sdxtech.net");
    QCoreApplication::setApplicationName("ProMind");

    ProMindWindow w;
    w.show();
    return a.exec();
}

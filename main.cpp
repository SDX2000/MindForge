#include <QApplication>

#include "qmind.h"
#include "mindmapwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("SDXTECH");
    QCoreApplication::setOrganizationDomain("sdxtech.net");
    QCoreApplication::setApplicationName("QMind");

    QMind w;
    w.show();
    return a.exec();
}

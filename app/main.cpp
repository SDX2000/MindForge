#include <QApplication>
#include <QFileDialog>

#include "mainwindow.h"
#include "mmwidget.h"
#include "mmnode.h"
#include "mmloader.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("SDXTECH");
    QCoreApplication::setOrganizationDomain("sdxtech.net");
    QCoreApplication::setApplicationName("MindForge");

    QFont font;
    font.setFamily("Droid Sans");
    app.setFont(font);

    MmMainWindow w;
//    QSettings settings;
//    MmWidget w(settings);

    w.openMindMap("C:\\Source\\C++\\Qt\\MindForge\\test\\input\\basic2");

    w.show();

    return app.exec();
}

#include <QApplication>
#include <QFileDialog>

#include <direct.h>

#include "mainwindow.h"
#include "mmwidget.h"
#include "mmnode.h"


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
    _chdir("C:\\Source\\C++\\Qt\\MindForge\\test\\input\\");
    w.openMindMap("basic2");
    w.show();

    return app.exec();
}

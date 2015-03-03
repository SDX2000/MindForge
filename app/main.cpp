#include <QApplication>
#include <QFileDialog>

#include "gui/mainwindow.h"
#include "gui/mmwidget.h"
#include "model/mmnode.h"
#include "model/mmloader.h"


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

    w.show();

    return app.exec();
}

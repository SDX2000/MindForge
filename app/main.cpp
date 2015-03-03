#include <QApplication>

#include "gui/mainwindow.h"
#include "gui/mmwidget.h"
#include "gui/mmnode.h"

MmNode getTestNodes()
{
    MmNode root("Root");
    root.addChild("Child 1");
    root.getChild(0).addChild("Grand child 1.1");
    root.getChild(0).addChild("Grand child 1.2");
    root.getChild(0).addChild("Grand child 1.3");
    root.addChild("Child 2");
    root.addChild("Child 3");

    return root;
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("SDXTECH");
    QCoreApplication::setOrganizationDomain("sdxtech.net");
    QCoreApplication::setApplicationName("MindForge");

    QFont font;
    font.setFamily("Droid Sans");
    app.setFont(font);

    if(argc > 2) {

    }


    MmNode root = getTestNodes();

    MmMainWindow w(root);
    w.show();
    return app.exec();
}
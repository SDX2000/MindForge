#include <QApplication>

#include "promindwindow.h"
#include "mmwidget.h"
#include "mmnodedata.h"

MmNodeData getTestNodes()
{
    MmNodeData root("Root");
    root.addChild("Child1");
    root.addChild("Child2");
    root.addChild("Child3");

    return root;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("SDXTECH");
    QCoreApplication::setOrganizationDomain("sdxtech.net");
    QCoreApplication::setApplicationName("ProMind");

    MmNodeData root = getTestNodes();

    ProMindWindow w(root);
    w.show();
    return a.exec();
}

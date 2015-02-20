#include <QApplication>

#include "promindwindow.h"
#include "mmwidget.h"
#include "mmnode.h"

MmNode getTestNodes()
{
    MmNode root("Root");
    root.addChild("Child1");
    root.addChild("Child2");
    root.addChild("Child3");

    return root;
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("SDXTECH");
    QCoreApplication::setOrganizationDomain("sdxtech.net");
    QCoreApplication::setApplicationName("ProMind");

    QFont font;
    font.setFamily("Droid Sans");
    app.setFont(font);

    MmNode::setDefaultFont(font);


    MmNode root = getTestNodes();

    MmMainWindow w(root);
    w.show();
    return app.exec();
}

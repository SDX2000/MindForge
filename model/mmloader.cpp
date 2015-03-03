#include "mmloader.h"

#include <QXmlStreamReader>

#include <stack>

using namespace std;

//MmNode MmLoader::load(QDir baseDir)
//{
//    MmNode root("Root");
//    root.addChild("Child 1");
//    root.getChild(0).addChild("Grand child 1.1");
//    root.getChild(0).addChild("Grand child 1.2");
//    root.getChild(0).addChild("Grand child 1.3");
//    root.addChild("Child 2");
//    root.addChild("Child 3");

//    return root;
//}


QString readAllText(QString filePath)
{
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw BadFile(filePath);
    }


    QTextStream in(&file);
    return in.readAll();
}


MmNode MmLoader::load(QDir baseDir)
{
    QString filePath = baseDir.absoluteFilePath("nodes.mf");
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly))
        throw BadFile(filePath);

    QXmlStreamReader xml;

    xml.setDevice(&file);


    MmNode superRoot;

    stack<MmNode*> nodeStack;

    nodeStack.push(&superRoot);

    while (!xml.atEnd()) {
        switch(xml.readNext()) {
            case QXmlStreamReader::StartElement:
                if (xml.name() == "node") {
                    QString id = xml.attributes().value("ID").toString();
                    QString nodeFilePath = baseDir.absoluteFilePath(QString("nodes/") + id);
                    MmNode &childNode = nodeStack.top()->addChild(readAllText(nodeFilePath));
                    nodeStack.push(&childNode);
                }
                break;
            case QXmlStreamReader::EndElement:
                if (xml.name() == "node") {
                    nodeStack.pop();
                }
                break;
        }
    }

    return superRoot.getChild(0);
}

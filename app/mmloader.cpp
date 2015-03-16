#include "common.h"
#include "mmloader.h"

#include <QXmlStreamReader>

#include <stack>

using namespace std;

QString readAllText(QString filePath)
{
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw BadFile(filePath);
    }

    QTextStream in(&file);
    return in.readAll();
}


MmNode* MmLoader::load(QDir baseDir)
{
    QString filePath = baseDir.absoluteFilePath("nodes.mf");
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly))
        throw BadFile(filePath);

    QXmlStreamReader xml;

    xml.setDevice(&file);

    //TODO: Properly dispose off superRoot (this is causing a memory leak right now).
    MmNode *superRoot = new  MmNode("");

    stack<MmNode*> nodeStack;

    nodeStack.push(superRoot);

    while (!xml.atEnd()) {
        switch(xml.readNext()) {
            case QXmlStreamReader::StartElement:
                if (xml.name() == "node") {
                    QString id = xml.attributes().value("ID").toString();
                    QString nodeFilePath = baseDir.absoluteFilePath(QString("nodes/") + id);
                    QString nodeText = readAllText(nodeFilePath);
                    MmNode &childNode
                            = nodeStack.top()
                              ->addChild(nodeText, id.toInt());
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

    return &superRoot->getChild(0);
}

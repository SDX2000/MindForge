#include <QMessageBox>
#include <QBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QXmlStreamReader>

#include <stack>

#include "exceptions.h"
#include "mmwidget.h"
#include "utils.h"

using namespace std;


MmWidget::MmWidget(QSettings &settings, QWidget *parent)
    : m_settings(settings)
    , QWidget(parent)
    , m_blackPen(Qt::black)
    , m_rootNode(NULL)
    , m_selectedNode(m_rootNode)
    , m_editor(this)
    , m_bAddNode(false)
{
    setSizePolicy(QSizePolicy::MinimumExpanding
                  , QSizePolicy::MinimumExpanding);
    m_blackPen.setWidth(2);
    connect(&m_editor, SIGNAL(editAccepted()), this, SLOT(editAccepted()));
    connect(&m_editor, SIGNAL(editRejected()), this, SLOT(editRejected()));
    m_editor.hide();

    setStyleSheet("border: 1px solid red");
}

MmNodeWidget* MmWidget::load(QDir baseDir)
{
    QString filePath = baseDir.absoluteFilePath("nodes.mf");
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly))
        throw BadFile(filePath);

    QXmlStreamReader xml;

    xml.setDevice(&file);

    MmNodeWidget *superRoot = new  MmNodeWidget("");

    stack<MmNodeWidget*> nodeStack;

    nodeStack.push(superRoot);

    while (!xml.atEnd()) {
        switch(xml.readNext()) {
            case QXmlStreamReader::StartElement:
                if (xml.name() == "node") {
                    QString id = xml.attributes().value("ID").toString();
                    QString nodeFilePath = baseDir.absoluteFilePath(QString("nodes/") + id);
                    QString nodeText = readAllText(nodeFilePath);
                    MmNodeWidget *childNode
                        = nodeStack.top()->addChild(nodeText, id.toInt());
                    nodeStack.push(childNode);
                }
                break;
            case QXmlStreamReader::EndElement:
                if (xml.name() == "node") {
                    nodeStack.pop();
                }
                break;
        }
    }

    MmNodeWidget * root = superRoot->getChild(0);
    root->setParent(NULL);
    delete superRoot;

    return root;
}

void MmWidget::openMindMap(QString path)
{
    if (m_rootNode) {
        m_rootNode->setParent(NULL);
        safe_delete(m_rootNode);
    }

    m_rootNode = load(QDir(path));
    m_rootNode->setParent(this);
    m_rootNode->show();
}

MmWidget::~MmWidget()
{
    safe_delete(m_rootNode);
}

void MmWidget::setData(MmNodeWidget *node)
{
    m_rootNode = node;
    m_rootNode->setParent(this);
}


void MmWidget::setBackGround(QColor color)
{
    QPalette p(palette());
    p.setColor(QPalette::Background, color);
    setPalette(p);
}

MmNodeWidget* MmWidget::getSelectedNode()
{
    return m_selectedNode;
}

void MmWidget::editNode()
{
    throw "Not yet implemented";
}

void MmWidget::addNode()
{
    m_bAddNode = true;
    m_selectedNode = getSelectedNode()->addChild("");
    editNode();
}

void MmWidget::editAccepted()
{
    qDebug()<<"Edit accepted.";
    m_bAddNode = false;
    m_selectedNode->setText(m_editor.toPlainText());
    m_editor.hide();
    update();
}

void MmWidget::editRejected()
{
    if (m_bAddNode) {
        m_selectedNode = static_cast<MmNodeWidget*>(getSelectedNode()->parent());
        m_selectedNode->removeLastChild();
        m_bAddNode = false;
    }
    m_editor.hide();
    update();
}

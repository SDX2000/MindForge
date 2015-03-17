#include <QMessageBox>
#include <QBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QEvent>


#include "mmwidget.h"
#include "common.h"
#include "mmloader.h"

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

void MmWidget::openMindMap(QString path)
{
    try {
        m_rootNode = MmLoader::load(QDir(path));
        m_rootNode->setParent(this);
    }
    catch(BadFile &ex) {
        QMessageBox::warning(this, "Could not open mind map.", ex.message());
    }
}

MmWidget::~MmWidget()
{
    delete m_rootNode;
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

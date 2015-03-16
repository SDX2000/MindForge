#include <QBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QEvent>


#include "mmwidget.h"
#include "common.h"


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
}

MmWidget::~MmWidget()
{
    delete m_rootNode;
}

void MmWidget::setData(MmNode *node)
{
    m_rootNode = node;
    if (layout() != m_rootNode->getLayout()) {
        delete layout();
        setLayout(m_rootNode->getLayout());
    }
    updateGeometry();
}


void MmWidget::setBackGround(QColor color)
{
    QPalette p(palette());
    p.setColor(QPalette::Background, color);
    setPalette(p);
}

MmNode* MmWidget::getSelectedNode()
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
    m_selectedNode = &getSelectedNode()->addChild("");
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
        m_selectedNode = getSelectedNode()->getParent();
        m_selectedNode->removeLastChild();
        m_bAddNode = false;
    }
    m_editor.hide();
    update();
}

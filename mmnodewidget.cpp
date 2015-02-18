#include "mmnodewidget.h"

#include <QLabel>
#include <QPainter>

MmNodeWidget::MmNodeWidget(MmNodeData &nodeData, QWidget *parent)
    : QLabel(parent)
    , m_nodeData(nodeData)
{
    //new QLabel(m_nodeData.getText(), this);
    setText(nodeData.getText());
    updateGeometry();
}

MmNodeWidget::~MmNodeWidget()
{

}


void MmNodeWidget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.setPen(QPen(Qt::red));
//    //painter.setBrush(QBrush(Qt::red));
//    painter.drawRect(rect());
}


#include <QBoxLayout>
#include <QLabel>
#include <QPainter>
#include <qevent.h>

#include "mmwidget.h"
#include "common.h"


MmWidget::MmWidget(MmNode data, QWidget *parent)
    : QWidget(parent)
{
    setData(data);
}

MmWidget::~MmWidget()
{

}

void MmWidget::setData(MmNode node)
{
    m_rootNode = node;
}



void MmWidget::setBackGround(QColor color)
{
    QPalette p(palette());
    p.setColor(QPalette::Background, color);
    setPalette(p);
}

void MmWidget::resizeEvent(QResizeEvent *)
{

}

void MmWidget::paintNode(MmNode node, QPainter &painter)
{
    QSize nodeSize = node.getDimensions();

    int y = -nodeSize.height()/2;


    painter.setPen(QPen(Qt::black));
    //painter.setBrush(QBrush(Qt::black));

    painter.drawText(0, y, nodeSize.width(), nodeSize.height()
                     , Qt::TextWrapAnywhere
                     , node.getText());


    painter.setPen(QPen(Qt::red));
    painter.drawRect(QRect(0, y, nodeSize.width(), nodeSize.height()));

    painter.translate(nodeSize.width() + MmNode::X_MARGIN, 0);

    int treeHeight = node.getTreeHeight();

    y = -treeHeight/2;

    foreach(MmNode childNode, node.getChildren())
    {
        painter.save();
        painter.translate(0,  y);
        paintNode(childNode, painter);
        painter.restore();

        y += childNode.getTreeHeight();
    }
}

void MmWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //Paint background
    painter.fillRect(rect(), palette().background());



    painter.translate(0, height()/2);
    paintNode(m_rootNode, painter);

}


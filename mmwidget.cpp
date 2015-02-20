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

void MmWidget::setData(MmNode nodeData)
{
    m_rootNodeData = nodeData;
}



void MmWidget::setBackGround(QColor color)
{
    QPalette p(palette());
    p.setColor(QPalette::Background, color);
    setPalette(p);
}

void MmWidget::resizeEvent(QResizeEvent *event)
{

}

void MmWidget::paintNode(MmNode nodeData, QPainter &painter)
{
    QSize size = nodeData.getDimensions();

    int _y = -size.height()/2;

    painter.drawText(0, _y, size.width(), size.height()
                     , Qt::TextWrapAnywhere
                     , nodeData.getText());

    int totalChildHeight = nodeData.getTreeHeight();

    foreach(MmNode childData, nodeData.getChildren())
    {

    }
}

void MmWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //Paint background
    painter.fillRect(rect(), palette().background());

//    painter.setPen(QPen(Qt::red));
//    painter.drawRect(m_nodeBounds);


    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(Qt::black));

    painter.translate(0, height()/2);
    paintNode(m_rootNodeData, painter);

}


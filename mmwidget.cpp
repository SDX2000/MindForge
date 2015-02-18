#include <QBoxLayout>
#include <QLabel>
#include <QPainter>
#include <qevent.h>

#include "mmwidget.h"
#include "common.h"
#include "mmnodewidget.h"

MmWidget::MmWidget(MmNodeData data, QWidget *parent)
    : QWidget(parent)
{
    setData(data);
}

MmWidget::~MmWidget()
{

}

void MmWidget::setData(MmNodeData nodeData)
{
    m_rootNodeData = nodeData;
    QLayout *baseLayout = createNodeWidgets(m_rootNodeData);
    setLayout(baseLayout);
}

QLayout* MmWidget::createNodeWidgets(MmNodeData &nodeData)
{
    QHBoxLayout *myLayout = new QHBoxLayout();
    myLayout->setSizeConstraint(QLayout::SetFixedSize);
    //myLayout->addWidget(new MmNodeWidget(nodeData));
    myLayout->addWidget(new QLabel(nodeData.getText()));

    QVBoxLayout *childNodeContainer = new QVBoxLayout();
    childNodeContainer->setSizeConstraint(QLayout::SetMinimumSize);

    foreach (MmNodeData childNodeData, nodeData.getChildren()) {
        childNodeContainer->addLayout(createNodeWidgets(childNodeData));
    }

    myLayout->addLayout(childNodeContainer);

    return myLayout;
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

void MmWidget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    //Paint background
//    painter.fillRect(rect(), palette().background());

//    painter.setPen(QPen(Qt::red));
//    painter.drawRect(m_nodeBounds);


//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setPen(QPen(Qt::black));
//    painter.setBrush(QBrush(Qt::black));

//    painter.drawText(0, 0, width(), height(), Qt::AlignVCenter | Qt::TextWrapAnywhere, m_rootNodeData.getText());

}


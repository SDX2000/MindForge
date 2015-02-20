#include <QBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QEvent>


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

    //TRACE(nodeSize);

    //TRACE(painter.font().family());

    QFontMetrics fm(painter.font(), painter.device());


    //TRACE(node.getText());
    //TRACE(fm.width(node.getText()));


    int y = -nodeSize.height()/2;

//    painter.setPen(QPen(Qt::red));
//    painter.drawRect(QRect(0, y, nodeSize.width(), nodeSize.height()));

    painter.setPen(QPen(Qt::black));

//    qDebug() << node.getText() << " " << nodeSize.width() <<  " x " << nodeSize.height() << endl;

    QRect br;
    painter.drawText(0, y, nodeSize.width(), nodeSize.height()
                     , Qt::TextWordWrap
                     , node.getText()
                     , &br);

    br.translate(0, 2);
    painter.drawLine(br.bottomLeft(), br.bottomRight());

    //TRACE(br);






    int totalInnerYMargin = node.getChildren().empty()? 0: MmNode::Y_MARGIN * ((int)node.getChildren().size() - 1);

    int treeHeight = node.getTreeHeight() + totalInnerYMargin;

    y = -treeHeight/2;



    foreach(MmNode childNode, node.getChildren())
    {
        painter.save();
        painter.translate(nodeSize.width(), br.bottom());

        QPainterPath path;
        path.cubicTo(MmNode::X_MARGIN/2 , 0, MmNode::X_MARGIN/2, y, MmNode::X_MARGIN, y);
        painter.drawPath(path);

        painter.translate(MmNode::X_MARGIN,  y);

        paintNode(childNode, painter);
        painter.restore();

        y += childNode.getTreeHeight() + MmNode::Y_MARGIN;
    }
}

void MmWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //Paint background
    painter.fillRect(rect(), palette().background());

    painter.setPen(QPen(Qt::red));

    painter.translate(0, height()/2);
    paintNode(m_rootNode, painter);
}


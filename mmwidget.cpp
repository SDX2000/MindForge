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

QRectF MmWidget::paintNode(MmNode node, QPainter &painter)
{

    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    QPen redPen(Qt::red);
    redPen.setWidth(1);


    painter.setPen(blackPen);

    QSize nodeSize = node.getDimensions();

    QDBG << SHOW(node.getText()) << SHOW(nodeSize.width()) <<  SHOW(nodeSize.height());

    double y = -nodeSize.height()/2.0;

    painter.setRenderHint(QPainter::Antialiasing, true);


    QRectF r(0.0, y, nodeSize.width(), nodeSize.height());
    QRectF br;

    painter.drawText(r
                     , Qt::TextWordWrap
                     , node.getText()
                     , &br);


    br.translate(0, 2);

    painter.drawLine(br.bottomLeft(), br.bottomRight());


//    painter.setPen(redPen);
//    painter.drawRect(br);
//    painter.setPen(blackPen);

    TRACE(br);


    double totalInnerYMargin = node.getChildren().empty()? 0: MmNode::Y_MARGIN * ((int)node.getChildren().size() - 1);

    double treeHeight = node.getTreeHeight() + totalInnerYMargin;

    y = -treeHeight/2.0;

    painter.translate(br.width(), br.bottom());




    foreach(MmNode childNode, node.getChildren())
    {
        painter.save();

        //Draw child node
        painter.translate(MmNode::X_MARGIN,  y);
        QRectF childBr = paintNode(childNode, painter).translated(MmNode::X_MARGIN, y);
        TRACE(childBr);
        painter.restore();

        //Draw connector from parent node to child node
        const double streach = 1.5;
        const int cp1X = br.right() + (childBr.left() - br.right())/2*streach;
        const int cp2X = br.right() + (childBr.left() - br.right())/2*(ceil(streach) - streach) ;

        QDBG << "Before cubicTo(): " << SHOW(br) << SHOW(cp1X) << SHOW(cp2X) << SHOW(childBr);

        QPainterPath path;
        path.cubicTo(cp1X , 0, cp2X, childBr.bottom(), childBr.left(), childBr.bottom());
        painter.drawPath(path);

        //Increment y for next child node.
        y += childNode.getTreeHeight() + MmNode::Y_MARGIN;
    }

    return br;
}

void MmWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    //Paint background
    painter.fillRect(rect(), palette().background());

    painter.translate(MmNode::X_MARGIN, height()/2);
    paintNode(m_rootNode, painter);
}


#include <QBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QEvent>


#include "mmwidget.h"
#include "common.h"


MmWidget::MmWidget(MmNode data, QSettings &settings, QWidget *parent)
    : m_settings(settings)
    , QWidget(parent)
    , m_xMargin(30)
    , m_yMargin(15)
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

QRectF MmWidget::paintNode(qreal _x, qreal _y, MmNode node, QPainter &painter)
{
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    QPen redPen(Qt::red);
    redPen.setWidth(1);

    painter.setPen(blackPen);

    QSize nodeSize = node.getDimensions();

    //QDBG << SHOW(node.getText()) << SHOW(nodeSize.width()) <<  SHOW(nodeSize.height());

    qreal x = _x;
    qreal y = _y - nodeSize.height()/2.0;

    painter.setRenderHint(QPainter::Antialiasing, true);


    QRectF r(x, y, nodeSize.width(), nodeSize.height());
    QRectF br;

    painter.drawText(r
                     , Qt::TextWordWrap
                     , node.getText()
                     , &br);

    painter.drawLine(br.bottomLeft(), br.bottomRight());
    //TRACE(br);

    qreal totalInnerYMargin = node.getChildren().empty()? 0: yMargin() * ((int)node.getChildren().size() - 1);

    qreal treeHeight = node.getTreeHeight() + totalInnerYMargin;

    const qreal Y_ADJUST = 5;

    y -= treeHeight/2.0 + Y_ADJUST;

    x += br.width() + xMargin();


    foreach(MmNode childNode, node.getChildren())
    {
        //Draw child node
        QRectF childBr = paintNode(x, y, childNode, painter);

        //Draw connector from parent node to child node
        QPainterPath path;
        path.moveTo(br.right(), br.bottom());

        const qreal cpX = br.right() + xMargin()/2;
        path.cubicTo(cpX, br.bottom(),
                     cpX, childBr.bottom(),
                     childBr.left(), childBr.bottom());
        painter.drawPath(path);

        //QDBG << "Before cubicTo(): " << SHOW(br) << SHOW(cp1X) << SHOW(cp2X) << SHOW(childBr);

        //Increment y for next child node.
        y += childNode.getTreeHeight() + yMargin();
    }

    return br;
}

void MmWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //Paint background
    painter.fillRect(rect(), palette().background());

    //painter.translate(xMargin(), height()/2);
    paintNode(xMargin(), height()/2, m_rootNode, painter);
}


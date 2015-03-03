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
    , m_blackPen(Qt::black)
{
    m_blackPen.setWidth(2);
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
    QSize nodeSize = node.getDimensions();

    qreal x = _x;
    qreal y = _y - nodeSize.height()/2.0;

    QRectF targetRect(x, y, nodeSize.width(), nodeSize.height());
    QRectF br;

    painter.setPen(m_blackPen);

    painter.drawText(targetRect
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

    painter.setRenderHint(QPainter::Antialiasing, true);

    //painter.translate(xMargin(), height()/2);
    paintNode(xMargin(), height()/2, m_rootNode, painter);
}

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
    , m_xMargin(30)
    , m_yMargin(15)
    , m_blackPen(Qt::black)
{
    m_blackPen.setWidth(2);
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

#define TRACELINE(C, X) \
    painter.save(); \
    painter.setPen(QPen(C)); \
    painter.drawLine X; \
    painter.restore();


#define TRACERECT(C, X) \
    painter.save(); \
    painter.setPen(QPen(C)); \
    painter.drawRect X; \
    painter.restore();

int serial=0;

void save(QImage *img)
{
    img->save(QString("mm%1.png").arg(serial++));
}


QRectF MmWidget::paintNode(qreal _x, qreal _y, MmNode node, QPainter &painter)
{
    QImage *img = (QImage*)painter.device();

//    TRACELINE(Qt::gray, (0,0, _x, _y));
//    save(img);

    QSize nodeSize = node.getDimensions();

    qreal x = _x;
    qreal y = _y - nodeSize.height()/2.0;

//    TRACELINE(Qt::blue, (_x, _y, x, y));
//    save(img);

    QRectF targetRect(x, y, nodeSize.width(), nodeSize.height());

//    TRACERECT(Qt::gray, (targetRect));
//    save(img);

    QRectF br;

    painter.setPen(m_blackPen);

    painter.drawText(targetRect
                     , Qt::TextWordWrap
                     , node.getText()
                     , &br);

    save(img);

    painter.drawLine(br.bottomLeft(), br.bottomRight());

//    save(img);

    //TRACE(br);

    qreal totalInnerYMargin = node.getChildren().empty()
                                ? 0
                                : yMargin() * ((int)node.getChildren().size() - 1);

    qreal treeHeight = node.getTreeHeight() + totalInnerYMargin;

    const qreal Y_ADJUST = 0;

    TRACELINE(Qt::gray, (0,0, x, y));
    save(img);

    _y -= treeHeight/2.0 + Y_ADJUST;

    _x += br.width() + xMargin();

    TRACELINE(Qt::red, (0, 0, _x, _y));
    save(img);

    TRACELINE(Qt::green, (_x, _y, _x, _y + treeHeight));
    save(img);

    foreach(MmNode childNode, node.getChildren())
    {
        //Draw child node
        QRectF childBr = paintNode(_x, _y, childNode, painter);

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
        _y += childNode.getTreeHeight() + yMargin();
    }

    return br;
}

void MmWidget::paintEvent(QPaintEvent *)
{
    //QPainter painter(this);
    QImage img(600, 600, QImage::Format_RGB32);
    QPainter painter(&img);


    //Paint background
    painter.fillRect(rect(), palette().background());

    save(&img);

    painter.setRenderHint(QPainter::Antialiasing, true);

    //painter.translate(xMargin(), height()/2);
    paintNode(xMargin(), height()/2, m_rootNode, painter);

    save(&img);
}

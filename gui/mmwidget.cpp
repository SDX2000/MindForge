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
#ifdef DUMP_FRAMES
    , m_img(800, 550, QImage::Format_RGB32)
    , m_px(400)
    , m_py(0)
#endif
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

#ifdef DUMP_FRAMES
void MmWidget::imgPrint(QString str, QPainter &painter)
{
    QRect targetRect(m_px, m_py, 800, 800);
    QRect br;
    painter.drawText(targetRect
                     , Qt::TextWordWrap
                     , str
                     , &br);

    m_py += br.height();
    save();
}


void MmWidget::save()
{
    m_img.save(QString("mm%1.png").arg(m_serial++));
}
#endif

QRect MmWidget::paintNode(int _x, int _y, MmNode node, QPainter &painter)
{
    QSize nodeSize = node.getDimensions();

    //Calculate the coordinates of the top-left point of the rectangle
    //in which the node text will be rendered
    int x = _x;
    int y = _y - nodeSize.height()/2;

    painter.setPen(m_blackPen);

    //Draw node text
    QRect targetRect(x, y, nodeSize.width(), nodeSize.height());
    QRect br;
    painter.drawText(targetRect
                     , Qt::TextWordWrap
                     , node.getText()
                     , &br);

    //Draw the line under the node text.
    painter.drawLine(br.bottomLeft(), br.bottomRight());

    if(node.getChildren().empty()) {
        return br;
    }

    const int Y_ADJUST = 0;

    //Move to top of child tree frame
    _y -= node.getTreeHeight()/2 + Y_ADJUST;

    //Move to the right clearing the width of the current node
    //plus some margin space
    _x += br.width() + node.xMargin();


    foreach(MmNode childNode, node.getChildren()) {
        _y += childNode.getTreeHeight()/2;

        //Draw child node
        QRect childBr = paintNode(_x, _y, childNode, painter);

        //Draw connector from parent node to child node
        QPainterPath path;
        path.moveTo(br.right(), br.bottom());

        const int cpX = br.right() + node.xMargin()/2;
        path.cubicTo(cpX, br.bottom(),
                     cpX, childBr.bottom(),
                     childBr.left(), childBr.bottom());
        painter.drawPath(path);

        //Increment y for next child node.
        _y += childNode.getTreeHeight()/2 + childNode.yMargin();
    }

    return br;
}

void MmWidget::paintEvent(QPaintEvent *)
{
#ifdef DUMP_FRAMES
    QPainter painter(&m_img);
#else
    QPainter painter(this);
#endif

    //Paint background
    painter.fillRect(rect(), palette().background());
    painter.drawRect(rect());

    painter.setRenderHint(QPainter::Antialiasing, true);

    //painter.translate(xMargin(), height()/2);
    paintNode(m_rootNode.xMargin(), height()/2, m_rootNode, painter);
    SAVE();
}

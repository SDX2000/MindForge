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

int MmWidget::yMargin()
{
    return m_yMargin;
}

int MmWidget::xMargin()
{
    return m_xMargin;
}

void MmWidget::setYMargin(int margin)
{
    m_yMargin = margin;
}

void MmWidget::setXMargin(int margin)
{
    m_xMargin = margin;
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

    int x = _x;
    int y = _y - nodeSize.height()/2;

    PRINT(QString("(x, y)=(%1, %2)").arg(x).arg(y), painter);

    QRect targetRect(x, y, nodeSize.width(), nodeSize.height());

    painter.setPen(m_blackPen);

    QRect br;
    painter.drawText(targetRect
                     , Qt::TextWordWrap
                     , node.getText()
                     , &br);

    //painter.setRenderHint(QPainter::Antialiasing, false);
    painter.drawLine(br.bottomLeft(), br.bottomRight());
    //painter.setRenderHint(QPainter::Antialiasing, true);

    PRINT(QString("(br.bottomLeft(), br.bottomLeft())=((%1, %2), (%3, %4))")
          .arg(br.bottomLeft().x())
          .arg(br.bottomLeft().y())
          .arg(br.bottomRight().x())
          .arg(br.bottomRight().y())
          , painter);

    int totalInnerYMargin = 0;
    int treeHeight = 0;

    if(node.getChildren().empty())
        return br;

    totalInnerYMargin = yMargin() * ((int)node.getChildren().size() - 1);
    treeHeight = node.getTreeHeight() + totalInnerYMargin;
    treeHeight -= node.getChild(0).getDimensions().height();


    const int Y_ADJUST = 0;

    TRACELINE(Qt::gray, (0,0, _x, _y));
    PRINT(QString("(_x, _y)=(%1, %2)").arg(_x).arg(_y), painter);
    PRINT(QString("treeHeight/2=%1").arg(treeHeight/2.0), painter);

    _y -= treeHeight/2.0 + Y_ADJUST;
    _x += br.width() + xMargin();

    TRACELINE(Qt::red, (0, 0, _x, _y));
    PRINT(QString("(_x, _y)=(%1, %2)").arg(_x).arg(_y), painter);

    TRACELINE(Qt::green, (_x, _y, _x, _y + treeHeight));


    TRACELINE(Qt::blue, (_x + 1, _y, _x + 1, _y + nodeSize.height()));
    PRINT(QString("nodeSize.height=%1").arg(nodeSize.height()), painter);

    foreach(MmNode childNode, node.getChildren())
    {
        //Draw child node
        QRect childBr = paintNode(_x, _y, childNode, painter);

        //Draw connector from parent node to child node
        QPainterPath path;
        path.moveTo(br.right(), br.bottom());

        const int cpX = br.right() + xMargin()/2;
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
#ifdef DUMP_FRAMES
    QPainter painter(&m_img);
#else
    QPainter painter(this);
#endif

    //Paint background
    painter.fillRect(rect(), palette().background());
    painter.drawRect(rect());
    SAVE();

    painter.setRenderHint(QPainter::Antialiasing, true);

    //painter.translate(xMargin(), height()/2);
    paintNode(xMargin(), height()/2, m_rootNode, painter);
    SAVE();
}

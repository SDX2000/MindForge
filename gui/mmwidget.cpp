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
    , m_selectedNode(&m_rootNode)
    , m_rootNode("Root")
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

void MmWidget::setData(const MmNode &node)
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

MmNode* MmWidget::getSelectedNode()
{
    return m_selectedNode;
}

void MmWidget::editNode()
{

}

void MmWidget::addNode()
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

    m_rootNode.paint(m_rootNode.xMargin(), height()/2, painter);
    SAVE();
}

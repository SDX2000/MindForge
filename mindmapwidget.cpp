#include <QPainter>
#include <qevent.h>

#include "mindmapwidget.h"
#include "common.h"

MindMapWidget::MindMapWidget(QWidget *parent)
    : QWidget(parent)
{
    m_bgColor = m_settings.value(BGCOLOR_KEY, QColor(Qt::white)).value<QColor>();
    m_doubleBuffer = new QPixmap(size());
}

MindMapWidget::~MindMapWidget()
{

}

void MindMapWidget::resizeEvent(QResizeEvent *event) {
    QSize newSize = event->size().expandedTo(m_doubleBuffer->size());

    if (m_doubleBuffer->size() != newSize){
        safe_delete(m_doubleBuffer);
        m_doubleBuffer = new QPixmap(newSize);
    }
}

void MindMapWidget::paintEvent(QPaintEvent *event) {
    QPainter dbPainter(m_doubleBuffer);
    dbPainter.fillRect(rect(), QBrush(m_bgColor));
    dbPainter.setRenderHint(QPainter::Antialiasing);
    dbPainter.setPen(QPen(Qt::red));
    dbPainter.drawLine(width()/8, height()/8, 7*width()/8, 7*height()/8);
    dbPainter.drawLine(width()/8, 7*height()/8, 7*width()/8, height()/8);
    QPainterPath myPath;
    myPath.moveTo(width()/8, height()/8);
    myPath.cubicTo(width()/8, 7*height()/8, 7*width()/8, height()/8, 7*width()/8, 7*height()/8);
    dbPainter.drawPath(myPath);

    QPainter painter(this);
    painter.drawPixmap(0,0, *m_doubleBuffer);
}


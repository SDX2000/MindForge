#include "mindmapwidget.h"

#include <QPainter>

MindMapWidget::MindMapWidget(QWidget *parent)
    : QWidget(parent)
{
    //setPalette(Qt::transparent);
    //setAttribute(Qt::WA_TransparentForMouseEvents);
}

MindMapWidget::~MindMapWidget()
{

}

void MindMapWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::red));
    painter.drawLine(width()/8, height()/8, 7*width()/8, 7*height()/8);
    painter.drawLine(width()/8, 7*height()/8, 7*width()/8, height()/8);
    //painter.moveTo(width()/8, height()/8);
    QPainterPath myPath;
    myPath.moveTo(width()/8, height()/8);
    myPath.cubicTo(width()/8, 7*height()/8, 7*width()/8, height()/8, 7*width()/8, 7*height()/8);
    painter.drawPath(myPath);
}


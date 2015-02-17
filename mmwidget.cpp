#include <QPainter>
#include <qevent.h>

#include "mmwidget.h"
#include "common.h"

MmWidget::MmWidget(MmNodeData data, QWidget *parent)
    : QWidget(parent)
    , m_data(data)
{

}

MmWidget::~MmWidget()
{

}

void MmWidget::setBackGround(QColor color)
{
    QPalette p(palette());
    p.setColor(QPalette::Background, color);
    setPalette(p);
}

void MmWidget::resizeEvent(QResizeEvent *event) {

}

void MmWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    //Paint background
    painter.fillRect(rect(), palette().background());


    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(Qt::black));

    painter.drawText(0, 0, width(), height(),Qt::AlignVCenter | Qt::TextWrapAnywhere, m_data.getText());

}


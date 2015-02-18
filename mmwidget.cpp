#include <QPainter>
#include <qevent.h>

#include "mmwidget.h"
#include "common.h"

MmWidget::MmWidget(MmNodeData data, QWidget *parent)
    : QWidget(parent)
{
    setData(data);
}

MmWidget::~MmWidget()
{

}
void MmWidget::setData(MmNodeData data)
{
    QFontMetrics fm(font());
    QRect m_nodeBounds = fm.boundingRect(0,0, MAX_NODE_WIDTH, height()
                    , Qt::AlignVCenter | Qt::TextWrapAnywhere
                    , m_data.getText());
    setMinimumSize(m_nodeBounds.size());
    m_data = data;
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

    painter.setPen(QPen(Qt::red));
    painter.drawRect(m_nodeBounds);


    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(Qt::black));

    painter.drawText(0, 0, width(), height(),Qt::AlignVCenter | Qt::TextWrapAnywhere, m_data.getText());

}


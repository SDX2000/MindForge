#include <QPaintEvent>

#include "qmind.h"
#include "ui_qmind.h"
#include "common.h"

QMind::QMind(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::QMind)
{
    m_ui->setupUi(this);
    setCentralWidget(&m_mindMapWidget);


}

QMind::~QMind()
{
    safe_delete(m_ui);
}


void QMind::resizeEvent(QResizeEvent *event) {
    m_mindMapWidget.resize(event->size());
    event->accept();
}

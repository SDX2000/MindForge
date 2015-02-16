#include <QPaintEvent>

#include "promind.h"
#include "ui_promind.h"
#include "common.h"

ProMind::ProMind(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::ProMind)
{
    m_ui->setupUi(this);
    setCentralWidget(&m_mindMapWidget);


}

ProMind::~ProMind()
{
    safe_delete(m_ui);
}


void ProMind::resizeEvent(QResizeEvent *event) {
    m_mindMapWidget.resize(event->size());
    event->accept();
}

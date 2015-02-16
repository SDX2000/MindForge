#include <QPaintEvent>

#include "promindwindow.h"
#include "ui_promind.h"
#include "common.h"

ProMindWindow::ProMindWindow(MmNodeData root, QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::ProMind)
    , m_mindMapWidget(root)
{
    m_ui->setupUi(this);
    setCentralWidget(&m_mindMapWidget);
}

ProMindWindow::~ProMindWindow()
{
    safe_delete(m_ui);
}


void ProMindWindow::resizeEvent(QResizeEvent *event) {
    m_mindMapWidget.resize(event->size());
    event->accept();
}

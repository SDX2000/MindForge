#include <QDirIterator>
#include <QPaintEvent>
#include<QDebug>

#include "promindwindow.h"
#include "ui_promind.h"
#include "common.h"

ProMindWindow::ProMindWindow(MmNodeData root, QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::ProMind)
    , m_mindMapWidget(root)
{
    m_ui->setupUi(this);

    m_bgColor = m_settings.value(BGCOLOR_KEY, QColor(Qt::white)).value<QColor>();
    m_mindMapWidget.setBackGround(m_bgColor);

    setCentralWidget(&m_mindMapWidget);

    addFonts();
}

void ProMindWindow::addFonts()
{
    QDirIterator it(":/fonts", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        qDebug() << it.next();
        m_fontDb.addApplicationFont(it.next());
    }

    foreach(QString s, m_fontDb.families())
    {
        qDebug() << s;
    }
}

ProMindWindow::~ProMindWindow()
{
    safe_delete(m_ui);
}


void ProMindWindow::resizeEvent(QResizeEvent *event) {
    m_mindMapWidget.resize(event->size());
    event->accept();
}

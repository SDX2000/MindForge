#include <QDirIterator>
#include <QPaintEvent>
#include<QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
#include "optionsdialog.h"

MmMainWindow::MmMainWindow(MmNode root, QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MindForge)
    , m_mindMapWidget(root, m_settings, this)
{
    m_ui->setupUi(this);

    m_bgColor = m_settings.value(BGCOLOR_KEY, QColor(Qt::white)).value<QColor>();
    m_mindMapWidget.setBackGround(m_bgColor);

    setCentralWidget(&m_mindMapWidget);

    addFonts();
}

void MmMainWindow::addFonts()
{
    QDirIterator it(":/fonts", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        //qDebug() << it.next();
        m_fontDb.addApplicationFont(it.next());
    }

//    foreach(QString s, m_fontDb.families())
//    {
//        qDebug() << s;
//    }
}

MmMainWindow::~MmMainWindow()
{
    safe_delete(m_ui);
}


void MmMainWindow::resizeEvent(QResizeEvent *event) {
    m_mindMapWidget.resize(event->size());
    event->accept();
}

void MmMainWindow::on_actionOptions_triggered()
{
    OptionsDialog od;
    od.exec();
}

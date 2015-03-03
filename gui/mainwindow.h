#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFontDatabase>
#include <QMainWindow>
#include <QSettings>
#include "mmwidget.h"

namespace Ui {
class MindForge;
}

class MmMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MmMainWindow(QWidget *parent = 0);
    ~MmMainWindow();



protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_actionOptions_triggered();

    void on_actionOpen_triggered();

private:
    void addFonts();

private:
    Ui::MindForge*    m_ui;
    MmWidget        m_mindMapWidget;
    QSettings       m_settings;

    QFontDatabase   m_fontDb;


    //Settings
private:
    const char*     BGCOLOR_KEY = "mindmap/bgcolor";
    QColor          m_bgColor;
};

#endif // MAINWINDOW_H

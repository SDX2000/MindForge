#ifndef PROMIND_H
#define PROMIND_H

#include <QFontDatabase>
#include <QMainWindow>
#include <QSettings>
#include "mmwidget.h"

namespace Ui {
class ProMind;
}

class MmMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MmMainWindow(MmNode root, QWidget *parent = 0);
    ~MmMainWindow();



protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_actionOptions_triggered();

private:
    void addFonts();

private:
    Ui::ProMind*    m_ui;
    MmWidget        m_mindMapWidget;
    QSettings       m_settings;

    QFontDatabase   m_fontDb;


    //Settings
private:
    const char*     BGCOLOR_KEY = "mindmap/bgcolor";
    QColor          m_bgColor;
};

#endif // PROMIND_H

#ifndef PROMIND_H
#define PROMIND_H

#include <QMainWindow>
#include <QSettings>
#include "mmwidget.h"

namespace Ui {
class ProMind;
}

class ProMindWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProMindWindow(MmNodeData root, QWidget *parent = 0);
    ~ProMindWindow();

protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::ProMind       *m_ui;
    MmWidget   m_mindMapWidget;
    QSettings       m_settings;
};

#endif // PROMIND_H

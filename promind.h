#ifndef PROMIND_H
#define PROMIND_H

#include <QMainWindow>
#include <QSettings>
#include "mmwidget.h"

namespace Ui {
class ProMind;
}

class ProMind : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProMind(QWidget *parent = 0);
    ~ProMind();

protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::ProMind       *m_ui;
    MindMapWidget   m_mindMapWidget;
    QSettings       m_settings;
};

#endif // PROMIND_H

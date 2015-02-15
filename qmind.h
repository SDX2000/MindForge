#ifndef QMIND_H
#define QMIND_H

#include <QMainWindow>
#include <QSettings>
#include "mindmapwidget.h"

namespace Ui {
class QMind;
}

class QMind : public QMainWindow
{
    Q_OBJECT

public:
    explicit QMind(QWidget *parent = 0);
    ~QMind();

protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::QMind       *m_ui;
    MindMapWidget   m_mindMapWidget;
    QSettings       m_settings;
};

#endif // QMIND_H

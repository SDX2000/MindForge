#ifndef MINDMAPWIDGET_H
#define MINDMAPWIDGET_H

#include <QSettings>
#include <QWidget>

class MindMapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MindMapWidget(QWidget *parent = 0);
    ~MindMapWidget();
protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
private:
    QSettings   m_settings;
    const char * BGCOLOR_KEY = "mindmap/bgcolor";
};

#endif // MINDMAPWIDGET_H

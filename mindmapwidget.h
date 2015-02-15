#ifndef MINDMAPWIDGET_H
#define MINDMAPWIDGET_H

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
};

#endif // MINDMAPWIDGET_H

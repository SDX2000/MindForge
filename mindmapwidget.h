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
    void resizeEvent(QResizeEvent *event);

signals:

public slots:
private:
    QSettings   m_settings;
    QPixmap     *m_doubleBuffer;
    QColor      m_bgColor;
    const char  *BGCOLOR_KEY = "mindmap/bgcolor";
};

#endif // MINDMAPWIDGET_H

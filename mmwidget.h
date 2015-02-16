#ifndef MINDMAPWIDGET_H
#define MINDMAPWIDGET_H

#include "mmnodedata.h"

#include <QSettings>
#include <QWidget>

class MmWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MmWidget(MmNodeData root, QWidget *parent = 0);
    ~MmWidget();
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

    MmNodeData  m_root;
};

#endif // MINDMAPWIDGET_H

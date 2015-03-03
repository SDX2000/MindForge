#ifndef MINDMAPWIDGET_H
#define MINDMAPWIDGET_H


#include "model/mmnode.h"

#include <QSettings>
#include <QWidget>
#include <QVector>

class MmWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MmWidget(QSettings &settings, QWidget *parent = 0);
    ~MmWidget();
    void setBackGround(QColor color);
    void setData(MmNode node);
    QRectF paintNode(qreal _x, qreal _y, MmNode node, QPainter &painter);


    int yMargin() {
        return m_yMargin;
    }

    int xMargin() {
        return m_xMargin;
    }

    void setYMargin(int margin) {
        m_yMargin = margin;
    }

    void setXMargin(int margin) {
        m_xMargin = margin;
    }

    //Constants
public:
    const int MAX_NODE_WIDTH = 800; //Pixels

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    QLayout* createNodeWidgets(MmNode &nodeData);

signals:

public slots:

private:
    QSettings           &m_settings;
    MmNode              m_rootNode;
    QVector<MmWidget>   m_children;
    QRect               m_nodeBounds;
    QPen                m_blackPen;

    //Settings
private:
    const char*     XMARGIN_KEY = "mindmap/xmargin";
    int             m_xMargin;

    const char*     YMARGIN_KEY = "mindmap/ymargin";
    int             m_yMargin;
};

#endif // MINDMAPWIDGET_H

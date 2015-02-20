#ifndef MINDMAPWIDGET_H
#define MINDMAPWIDGET_H


#include "mmnode.h"

#include <QSettings>
#include <QWidget>
#include <QVector>

class MmWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MmWidget(MmNode data, QWidget *parent = 0);
    ~MmWidget();
    void setBackGround(QColor color);
    void setData(MmNode node);
    void paintNode(MmNode node, QPainter &painter);

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
    QSettings           m_settings;
    MmNode          m_rootNode;
    QVector<MmWidget>   m_children;
    int                 m_margins;//l,t,r,b
    QRect               m_nodeBounds;
};

#endif // MINDMAPWIDGET_H

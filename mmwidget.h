#ifndef MINDMAPWIDGET_H
#define MINDMAPWIDGET_H


#include "mmnodedata.h"

#include <QSettings>
#include <QWidget>
#include <QVector>

class MmWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MmWidget(MmNodeData data, QWidget *parent = 0);
    ~MmWidget();
    void setBackGround(QColor color);
    void setData(MmNodeData nodeData);

    //Constants
public:
    const int MAX_NODE_WIDTH = 800; //Pixels

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    QLayout* createNodeWidgets(MmNodeData &nodeData);

signals:

public slots:

private:
    QSettings           m_settings;
    MmNodeData          m_rootNodeData;
    QVector<MmWidget>   m_children;
    int                 m_margins;//l,t,r,b
    QRect               m_nodeBounds;
};

#endif // MINDMAPWIDGET_H

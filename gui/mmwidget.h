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
    QRect paintNode(int _x, int _y, MmNode node, QPainter &painter);

#ifdef DUMP_FRAMES
    void save();
    void imgPrint(QString str, QPainter &painter);
#endif


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

#ifdef DUMP_FRAMES
    int m_serial=0;
    int m_px;
    int m_py;
    QImage m_img;
#endif
};

#ifdef DUMP_FRAMES
    #define SAVE() save()
    #define PRINT(S) imgPrint(S, painter)

    #define TRACELINE(C, X) \
        painter.save(); \
        painter.setPen(QPen(C)); \
        painter.drawLine X; \
        painter.restore();

    #define TRACERECT(C, X) \
        painter.save(); \
        painter.setPen(QPen(C)); \
        painter.drawRect X; \
        painter.restore();

#else
    #define SAVE()
    #define PRINT(S)
    #define TRACELINE(C, X)
    #define TRACERECT(C, X)
#endif

#endif // MINDMAPWIDGET_H

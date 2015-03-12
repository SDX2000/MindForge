#ifndef MINDMAPWIDGET_H
#define MINDMAPWIDGET_H


#include "model/mmnode.h"

#include "mmtextedit.h"

#include <QSettings>
#include <QWidget>
#include <QVector>
#include <QTextEdit>
#include <QPlainTextEdit>

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

class MmWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MmWidget(QSettings &settings, QWidget *parent = 0);
    ~MmWidget();
    void setBackGround(QColor color);
    void setData(const MmNode &node);
    MmNode* getSelectedNode();
    void editNode();
    void addNode();


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
    void editAccepted();
    void editRejected();

private:
    QSettings          &m_settings;
    MmNode              m_rootNode;
    MmNode             *m_selectedNode;
    QPen                m_blackPen;
    MmTextEdit          m_editor;
    bool                m_bAddNode;

#ifdef DUMP_FRAMES
    int m_serial=0;
    int m_px;
    int m_py;
    QImage m_img;
#endif
};

#endif // MINDMAPWIDGET_H

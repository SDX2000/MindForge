#ifndef MINDMAPWIDGET_H
#define MINDMAPWIDGET_H


#include "mmnode.h"

#include "mmtextedit.h"

#include <QSettings>
#include <QWidget>
#include <QVector>
#include <QTextEdit>
#include <QPlainTextEdit>

class MmWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MmWidget(QSettings &settings, QWidget *parent = 0);
    ~MmWidget();
    void setBackGround(QColor color);
    void setData(MmNode *node);
    MmNode* getSelectedNode();
    void editNode();
    void addNode();

    //Constants
public:
    const int MAX_NODE_WIDTH = 800; //Pixels

signals:

public slots:
    void editAccepted();
    void editRejected();

private:
    QSettings          &m_settings;
    MmNode             *m_rootNode;
    MmNode             *m_selectedNode;
    QPen                m_blackPen;
    MmTextEdit          m_editor;
    bool                m_bAddNode;
};

#endif // MINDMAPWIDGET_H

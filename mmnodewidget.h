#ifndef MMNODEWIDGET_H
#define MMNODEWIDGET_H

#include "mmnodedata.h"

#include <QLabel>
#include <QWidget>

class MmNodeWidget : public QLabel
{
    Q_OBJECT
public:
    explicit MmNodeWidget(MmNodeData &nodeData, QWidget *parent = 0);
    ~MmNodeWidget();

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    MmNodeData &m_nodeData;
};

#endif // MMNODEWIDGET_H

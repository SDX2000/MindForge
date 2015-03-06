#ifndef MMNODEDATA_H
#define MMNODEDATA_H

#include <QCoreApplication>
#include <QFont>
#include <QFontMetrics>
#include <QObject>
#include <QPainter>
#include <QString>
#include <vector>

#include "common.h"


class MmNode
{
public:
    const int MAX_WIDTH = 800;

    MmNode();
    explicit MmNode(QString text);
    ~MmNode();
    const QString& getText() const;
    void setText(QString text);
    MmNode& addChild(QString text);
    MmNode& addChild(MmNode child);
    MmNode& getChild(int index);
    std::vector<MmNode> getChildren();
    void setFont(const QFont &font);
    const QFont& getFont();
    QSize getDimensions();
    void updateDimensions();
    int getTreeHeight();
    const MmNode& operator = (const MmNode& rhs);

private:
    QString                 m_text;
    QSize                   m_size;
    std::vector<MmNode>     m_children;
    QFont                   m_font;
};

#endif // MMNODEDATA_H

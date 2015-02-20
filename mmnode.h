#ifndef MMNODEDATA_H
#define MMNODEDATA_H

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
    static const int MAX_WIDTH = 800;
    static const int Y_MARGIN = 20;
    static const int X_MARGIN = 50;

    MmNode()
        :mb_fontSet(false)
    {
        updateDimensions();
    }

    explicit MmNode(QString text)
        : m_text(text)
        , mb_fontSet(false)
    {
        updateDimensions();
    }

    ~MmNode()
    {
    }

    const QString& getText() const
    {
        return m_text;
    }

    void setText(QString text)
    {
        m_text = text;
        updateDimensions();
    }

    void addChild(QString text)
    {
        m_children.push_back(MmNode(text));
    }

    void addChild(MmNode child)
    {
        m_children.push_back(child);
    }

    MmNode& getChild(int index)
    {
        return m_children.at(index);
    }

    std::vector<MmNode> getChildren()
    {
        return m_children;
    }

    void setFont(const QFont &font)
    {
        mb_fontSet = true;
        m_font = font;
        updateDimensions();
    }

    const QFont& getFont()
    {
        return m_font;
    }

    QSize getDimensions()
    {
        return m_size;
    }

    void updateDimensions()
    {
        QFont &font = mb_fontSet? m_font : sm_defaultFont;
        QFontMetrics fm(font);
        m_size = fm.boundingRect(0 ,0 , MAX_WIDTH, 0
                               , Qt::AlignLeft | Qt::TextWordWrap
                               , m_text).size();
    }

    int getTreeHeight()
    {
        if (m_children.empty())
            return  m_size.height() + Y_MARGIN;

        int treeHeight = 0;

        foreach(MmNode childNodeData, m_children)
        {
            treeHeight += childNodeData.getTreeHeight();
        }

        return max(treeHeight, m_size.height());
    }

    const MmNode& operator = (const MmNode& rhs)
    {
        m_text      = rhs.m_text;
        m_children  = rhs.m_children;
        m_font      = rhs.m_font;
        mb_fontSet  = rhs.mb_fontSet;
        return *this;
    }

    static QFont getDefaultFont() {
        return sm_defaultFont;
    }

    static void setDefaultFont(QFont font) {
        sm_defaultFont = font;
    }

private:
    QString                 m_text;
    QSize                   m_size;
    int                     m_x;
    int                     m_y;
    std::vector<MmNode> m_children;
    QFont                   m_font;
    bool                    mb_fontSet;
    static QFont            sm_defaultFont;
};

#endif // MMNODEDATA_H

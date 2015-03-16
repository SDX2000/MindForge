#ifndef MMNODEDATA_H
#define MMNODEDATA_H

#include <QCoreApplication>
#include <QFont>
#include <QFontMetrics>
#include <QObject>
#include <QPainter>
#include <QString>
#include <vector>

class MmNode
{
public:
    const int MAX_WIDTH = 800;

    explicit MmNode(MmNode *parent=NULL);
    explicit MmNode(QString text, MmNode *parent=NULL);
    explicit MmNode(QString text, int id, MmNode *parent=NULL);
    ~MmNode();
    const QString& getText() const;
    void setText(QString text);
    void setPos(int x, int y);

    MmNode& addChild(QString text);
    MmNode& addChild(QString text, int id);
    MmNode& getChild(int index);
    std::vector<MmNode> getChildren();
    void removeLastChild();

    void setFont(const QFont &font);
    const QFont& getFont();
    const QRect& getTextRect() const;

    int getTreeHeight();
    const MmNode& operator = (const MmNode& rhs);
    int yMargin();
    int xMargin();
    void setYMargin(int margin);
    void setXMargin(int margin);
    MmNode *getParent() const;
    int getId() const;
    void paint(QPainter &painter);
    void updateLayout();

protected:
    void updateTextRect();

private:
    QString                 m_text;
    std::vector<MmNode>     m_children;
    QFont                   m_font;
    int                     m_id;
    MmNode                  *m_parent;
    QRect                   m_textRect;

    //Settings
private:
    const char*     XMARGIN_KEY = "mindmap/xmargin";
    int             m_xMargin;

    const char*     YMARGIN_KEY = "mindmap/ymargin";
    int             m_yMargin;

    //Static members
private:
    static int      sm_lastId;
};

#endif // MMNODEDATA_H

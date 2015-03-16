#include "common.h"
#include "mmnode.h"


int MmNode::sm_lastId = 0;

static const int XMARGIN = 30;
static const int YMARGIN = 27;


MmNode::MmNode(MmNode *parent)
    : m_parent(parent)
    , m_xMargin(XMARGIN)
    , m_yMargin(YMARGIN)
    , m_textRect(0, 0, 0, 0)
{
    updateTextRect();
    m_id = ++sm_lastId;
}

MmNode::MmNode(QString text, MmNode *parent)
    : m_text(text)
    , m_parent(parent)
    , m_xMargin(XMARGIN)
    , m_yMargin(YMARGIN)
    , m_textRect(0, 0, 0, 0)
{
    updateTextRect();
    m_id = ++sm_lastId;
}


MmNode::MmNode(QString text, int id, MmNode *parent)
    : m_text(text)
    , m_id(id)
    , m_parent(parent)
    , m_xMargin(XMARGIN)
    , m_yMargin(YMARGIN)
    , m_textRect(0, 0, 0, 0)
{
    updateTextRect();
    sm_lastId = max(sm_lastId, id);
}

MmNode::~MmNode()
{
}

const QString& MmNode::getText() const
{
    return m_text;
}

void MmNode::setText(QString text)
{
    m_text = text;
    updateTextRect();
}

int MmNode::getId() const
{
    return m_id;
}

MmNode* MmNode::getParent() const
{
    return m_parent;
}


MmNode& MmNode::addChild(QString text)
{
    m_children.push_back(MmNode(text, this));
    return m_children[m_children.size() - 1];
}

MmNode& MmNode::addChild(QString text, int id)
{
    m_children.push_back(MmNode(text, id, this));
    return m_children[m_children.size() - 1];
}

void MmNode::removeLastChild()
{
    m_children.pop_back();
}

MmNode& MmNode::getChild(int index)
{
    return m_children.at(index);
}

std::vector<MmNode> MmNode::getChildren()
{
    return m_children;
}

void MmNode::setFont(const QFont &font)
{
    m_font = font;
    updateTextRect();
}

const QFont& MmNode::getFont()
{
    return m_font;
}

int MmNode::yMargin()
{
    return m_yMargin;
}

int MmNode::xMargin()
{
    return m_xMargin;
}

void MmNode::setYMargin(int margin)
{
    m_yMargin = margin;
}

void MmNode::setXMargin(int margin)
{
    m_xMargin = margin;
}

void MmNode::updateTextRect()
{
    QString text = m_text;
    if(!text.length()) {
        text = "WWW"; //Reserve space wide enough for 3 Ws atleast.
    }

    QFontMetrics fm(m_font);

    m_textRect = fm.boundingRect(m_textRect.x(), m_textRect.y(), MAX_WIDTH, 0
                           , Qt::AlignLeft | Qt::TextWordWrap
                           , text);
}

int MmNode::getTreeHeight()
{
    if (m_children.empty())
        return m_textRect.height();

    int treeHeight = 0;

    foreach(MmNode childNodeData, m_children)
    {
        treeHeight += childNodeData.getTreeHeight();
    }

    treeHeight += ((int)m_children.size() -  1) * yMargin();

    //TODO: Check if we need to add treeHeight/2 to m_size.height()
    //for the case when the node height is greater than the height of the child
    //subtree but part (half) of the child subtree is sticking out of the bottom.
    return max(treeHeight, m_textRect.height());
}

const MmNode& MmNode::operator = (const MmNode& rhs)
{
    m_text      = rhs.m_text;
    m_children  = rhs.m_children;
    m_font      = rhs.m_font;
    m_id        = rhs.m_id;
    m_parent    = rhs.m_parent;
    m_textRect  = rhs.m_textRect;
    m_xMargin   = rhs.m_xMargin;
    m_yMargin   = rhs.m_yMargin;

    return *this;
}


const QRect& MmNode::getTextRect() const
{
    return m_textRect;
}

void MmNode::setPos(int x, int y)
{
    m_textRect.setRect(x, y, m_textRect.width(), m_textRect.height());
}

void MmNode::updateLayout()
{
    if(m_children.empty()) {
        return;
    }

    const int Y_ADJUST = 0;

    int _x = m_textRect.x();
    int _y = m_textRect.y();

    //Move to top of child tree frame
    _y -= getTreeHeight()/2 + Y_ADJUST;

    //Move to the right clearing the width of the current node
    //plus some margin space
    _x += m_textRect.width() + xMargin();

    for (int i = 0; i < m_children.size(); ++i) {
        MmNode &childNode = m_children[i];

        _y += childNode.getTreeHeight()/2;

        childNode.setPos(_x, _y);

        childNode.updateLayout();

        //Increment y for next child node.
        _y += childNode.getTreeHeight()/2 + childNode.yMargin();
    }
}


void MmNode::paint(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 2));

    //Draw node text
    painter.drawText(m_textRect
                     , Qt::TextWordWrap
                     , getText()
                     , &m_textRect);

    //Draw the line under the node text.
    painter.drawLine(m_textRect.bottomLeft(), m_textRect.bottomRight());

    for (int i = 0; i < m_children.size(); ++i) {
        MmNode &childNode = m_children[i];
        //Draw child node
        childNode.paint(painter);

        //Draw connector from parent node to child node
        QRect childTextRect = childNode.getTextRect();

        QPainterPath path;
        path.moveTo(m_textRect.right(), m_textRect.bottom());
        const int cpX = m_textRect.right() + xMargin()/2;
        path.cubicTo(cpX, m_textRect.bottom(),
                     cpX, childTextRect.bottom(),
                     childTextRect.left(), childTextRect.bottom());

        painter.drawPath(path);
    }
}

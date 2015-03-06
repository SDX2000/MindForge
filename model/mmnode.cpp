#include "mmnode.h"


int MmNode::sm_lastId = 0;

static const int XMARGIN = 30;
static const int YMARGIN = 27;


MmNode::MmNode(QString text, MmNode *parent)
    : m_text(text)
    , m_parent(parent)
    , m_xMargin(XMARGIN)
    , m_yMargin(YMARGIN)
{
    updateDimensions();
    m_id = ++sm_lastId;
}


MmNode::MmNode(QString text, int id, MmNode *parent)
    : m_text(text)
    , m_id(id)
    , m_parent(parent)
    , m_xMargin(XMARGIN)
    , m_yMargin(YMARGIN)
{
    updateDimensions();
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
    updateDimensions();
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
    updateDimensions();
}

const QFont& MmNode::getFont()
{
    return m_font;
}

QSize MmNode::getDimensions()
{
    return m_size;
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

void MmNode::updateDimensions()
{
    QFontMetrics fm(m_font);
    m_size = fm.boundingRect(0 ,0 , MAX_WIDTH, 0
                           , Qt::AlignLeft | Qt::TextWordWrap
                           , m_text).size();
}

int MmNode::getTreeHeight()
{
    if (m_children.empty())
        return m_size.height();

    int treeHeight = 0;

    foreach(MmNode childNodeData, m_children)
    {
        treeHeight += childNodeData.getTreeHeight();
    }

    treeHeight += ((int)m_children.size() -  1) * yMargin();

    return max(treeHeight, m_size.height());
}

const MmNode& MmNode::operator = (const MmNode& rhs)
{
    m_text      = rhs.m_text;
    m_size      = rhs.m_size;
    m_children  = rhs.m_children;
    m_font      = rhs.m_font;
    return *this;
}


const QRect& MmNode::getTextRect() const
{
    return m_textRect;
}

void MmNode::paint(int _x, int _y, QPainter &painter)
{
    QSize nodeSize = getDimensions();

    //Calculate the coordinates of the top-left point of the rectangle
    //in which the node text will be rendered
    int x = _x;
    int y = _y - nodeSize.height()/2;


    painter.setPen(QPen(Qt::black, 2));

    //Draw node text
    QRect targetRect(x, y, nodeSize.width(), nodeSize.height());
    painter.drawText(targetRect
                     , Qt::TextWordWrap
                     , getText()
                     , &m_textRect);

    //Draw the line under the node text.
    painter.drawLine(m_textRect.bottomLeft(), m_textRect.bottomRight());

    if(getChildren().empty()) {
        return;
    }

    const int Y_ADJUST = 0;

    //Move to top of child tree frame
    _y -= getTreeHeight()/2 + Y_ADJUST;

    //Move to the right clearing the width of the current node
    //plus some margin space
    _x += m_textRect.width() + xMargin();


    foreach(MmNode childNode, getChildren()) {
        _y += childNode.getTreeHeight()/2;

        //Draw child node
        childNode.paint(_x, _y, painter);
        QRect childTextRect = childNode.getTextRect();
        //Draw connector from parent node to child node
        QPainterPath path;
        path.moveTo(m_textRect.right(), m_textRect.bottom());

        const int cpX = m_textRect.right() + xMargin()/2;
        path.cubicTo(cpX, m_textRect.bottom(),
                     cpX, childTextRect.bottom(),
                     childTextRect.left(), childTextRect.bottom());
        painter.drawPath(path);

        //Increment y for next child node.
        _y += childNode.getTreeHeight()/2 + childNode.yMargin();
    }
}

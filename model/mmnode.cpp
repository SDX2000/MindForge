#include "mmnode.h"


int MmNode::sm_lastId = 0;

static const int XMARGIN = 30;
static const int YMARGIN = 27;


MmNode::MmNode()
    : m_xMargin(XMARGIN)
    , m_yMargin(YMARGIN)
{
    updateDimensions();
    m_id = ++sm_lastId;
}

MmNode::MmNode(QString text, int id)
    : m_text(text)
    , m_id(id)
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

MmNode& MmNode::addChild(QString text)
{
    m_children.push_back(MmNode());
    MmNode &node = m_children[m_children.size() - 1];
    node.setText(text);
    return node;
}

MmNode& MmNode::addChild(QString text, int id)
{
    m_children.push_back(MmNode(text, id));
    return m_children[m_children.size() - 1];
}

MmNode& MmNode::addChild(MmNode child)
{
    m_children.push_back(child);
    return m_children[m_children.size() - 1];
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

#include "common.h"
#include "mmnode.h"


int MmNode::sm_lastId = 0;

static const int XMARGIN = 30;
static const int YMARGIN = 27;


MmNode::MmNode(MmNode *parent)
    : m_parent(parent)
    , m_xMargin(XMARGIN)
    , m_yMargin(YMARGIN)
    , m_pHBox(new QHBoxLayout())
    , m_pVBox(new QVBoxLayout())
    , m_pLabel(new QLabel())
{
    m_id = ++sm_lastId;
}

MmNode::MmNode(QString text, MmNode *parent)
    : m_parent(parent)
    , m_xMargin(XMARGIN)
    , m_yMargin(YMARGIN)
    , m_pHBox(new QHBoxLayout())
    , m_pVBox(new QVBoxLayout())
    , m_pLabel(new QLabel())

{
    m_pLabel->setText(text);
    m_id = ++sm_lastId;
}


MmNode::MmNode(QString text, int id, MmNode *parent)
    : m_id(id)
    , m_parent(parent)
    , m_xMargin(XMARGIN)
    , m_yMargin(YMARGIN)
    , m_pHBox(new QHBoxLayout())
    , m_pVBox(new QVBoxLayout())
    , m_pLabel(new QLabel())
{
    m_pLabel->setText(text);
    sm_lastId = max(sm_lastId, id);
}

MmNode::~MmNode()
{
}

QString MmNode::getText() const
{
    return m_pLabel->text();
}

void MmNode::setText(QString text)
{
    m_pLabel->setText(text);
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

    m_children.push_back(MmNode(text, this));
    MmNode &node = m_children[m_children.size() - 1];

    if(m_pVBox->count()) {
        m_pVBox->addSpacing(m_yMargin);
    }

    m_pVBox->addLayout(node.m_pHBox);
    return node;
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

//const MmNode& MmNode::operator = (const MmNode& rhs)
//{
//    m_children  = rhs.m_children;
//    m_id        = rhs.m_id;
//    m_parent    = rhs.m_parent;
//    m_xMargin   = rhs.m_xMargin;
//    m_yMargin   = rhs.m_yMargin;

//    return *this;
//}

QLayout* MmNode::getLayout()
{
    return m_pHBox;
}

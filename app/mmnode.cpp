#include "utils.h"
#include "mmnode.h"


int MmNodeWidget::sm_lastId = 0;

static const int XMARGIN = 30;
static const int YMARGIN = 27;


MmNodeWidget::MmNodeWidget(QWidget *parent)
    : QWidget(parent)
{
    init("", sm_lastId + 1);
}

MmNodeWidget::MmNodeWidget(QString text, QWidget *parent)
    : QWidget(parent)
{
    init(text, sm_lastId + 1);
}

MmNodeWidget::MmNodeWidget(QString text, int id, QWidget *parent)
    :QWidget(parent)
{
    init(text, id);
}

void MmNodeWidget::init(QString text, int id)
{
    m_xMargin = XMARGIN;
    m_yMargin = YMARGIN;
    m_pHBox = new QHBoxLayout();
    m_pVBox = new QVBoxLayout();
    m_pLabel = new QLabel();
    m_id = id;
    sm_lastId = max(sm_lastId, id);

    m_pLabel->setText(text);

    m_pHBox->addWidget(m_pLabel);
    m_pHBox->addSpacing(m_xMargin);
    m_pHBox->addLayout(m_pVBox);

    setStyleSheet("border: 1px solid red");
    setLayout(m_pHBox);
}

MmNodeWidget::~MmNodeWidget()
{
}

QString MmNodeWidget::getText() const
{
    return m_pLabel->text();
}

void MmNodeWidget::setText(QString text)
{
    m_pLabel->setText(text);
}

int MmNodeWidget::getId() const
{
    return m_id;
}

MmNodeWidget* MmNodeWidget::addChild(QString text)
{
    MmNodeWidget *node = new MmNodeWidget(text);
    m_children.push_back(node);

    if(m_pVBox->count()) {
        m_pVBox->addSpacing(m_yMargin);
    }

    m_pVBox->addWidget(node);

    return node;
}

MmNodeWidget* MmNodeWidget::addChild(QString text, int id)
{
    MmNodeWidget *node = new MmNodeWidget(text, id);
    m_children.push_back(node);
    m_pVBox->addWidget(node);
    return node;
}

void MmNodeWidget::removeLastChild()
{
    m_children.pop_back();
}

MmNodeWidget* MmNodeWidget::getChild(int index)
{
    return m_children.at(index);
}

int MmNodeWidget::yMargin()
{
    return m_yMargin;
}

int MmNodeWidget::xMargin()
{
    return m_xMargin;
}

void MmNodeWidget::setYMargin(int margin)
{
    m_yMargin = margin;
}

void MmNodeWidget::setXMargin(int margin)
{
    m_xMargin = margin;
}

#include <QPainter>

#include "utils.h"
#include "mmnodewidget.h"


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
    QHBoxLayout *hbox = new QHBoxLayout();
    m_pVBox = new QVBoxLayout();
    m_pLabel = new QLabel();
    m_id = id;
    sm_lastId = max(sm_lastId, id);

    QVBoxLayout *vbox1 = new QVBoxLayout();
    vbox1->addStretch();
    vbox1->addWidget(m_pLabel);
    vbox1->addStretch();

    m_pLabel->setText(text);

    //m_pHBox->addWidget(m_pLabel);
    hbox->addLayout(vbox1);
    hbox->addSpacing(m_xMargin);
    hbox->addLayout(m_pVBox);

    //setStyleSheet("border: 1px solid red");
    setLayout(hbox);
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

void MmNodeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(Qt::black, 2));

    QRect rect = m_pLabel->geometry().translated(0, 2);

    painter.drawLine(rect.bottomLeft(), rect.bottomRight());

    for (int i = 0; i < m_children.size(); ++i) {
        MmNodeWidget *child = m_children[i];

        QRect crect = ::mapToParent(child, child->m_pLabel->geometry())
                      .translated(0, 2);

        const int cpX = rect.right() + xMargin()/2;

        QPoint start(rect.bottomRight());
        QPoint cp1(cpX, rect.bottom());
        QPoint cp2(cpX, crect.bottom());
        QPoint end(crect.bottomLeft());

        QPainterPath path;
        path.moveTo(start);
        path.cubicTo(cp1, cp2, end);

        painter.drawPath(path);
    }
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

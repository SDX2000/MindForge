#include "mmnodedata.h"

MmNodeData::MmNodeData()
{

}

MmNodeData::MmNodeData(QString text)
    :m_text(text)
{

}

MmNodeData::~MmNodeData()
{

}


const QString& MmNodeData::getText() const
{
    return m_text;
}

void MmNodeData::setText(QString text)
{
    m_text = text;
}

void MmNodeData::addChild(QString text)
{
    m_children.push_back(MmNodeData(text));
}

void MmNodeData::addChild(MmNodeData child)
{
    m_children.push_back(child);
}

MmNodeData& MmNodeData::getChild(int index)
{
    return m_children.at(index);
}

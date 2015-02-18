#ifndef MMNODEDATA_H
#define MMNODEDATA_H

#include <QObject>
#include <QString>
#include <vector>


class MmNodeData
{
public:
    MmNodeData()
    {
    }

    MmNodeData(QString text)
        :m_text(text)
    {
    }

    ~MmNodeData()
    {
    }

    const QString& getText() const
    {
        return m_text;
    }

    void setText(QString text)
    {
        m_text = text;
    }

    void addChild(QString text)
    {
        m_children.push_back(MmNodeData(text));
    }

    void addChild(MmNodeData child)
    {
        m_children.push_back(child);
    }

    MmNodeData& getChild(int index)
    {
        return m_children.at(index);
    }

    std::vector<MmNodeData> getChildren()
    {
        return m_children;
    }

private:
    QString m_text;
    std::vector<MmNodeData> m_children;
};

#endif // MMNODEDATA_H

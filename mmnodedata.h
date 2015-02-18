#ifndef MMNODEDATA_H
#define MMNODEDATA_H

#include <QObject>
#include <QString>
#include <vector>


class MmNodeData
{
public:
    MmNodeData();
    MmNodeData(QString text);
    ~MmNodeData();

    const QString& getText() const;
    void setText(QString text);
    void addChild(QString text);
    void addChild(MmNodeData child);
    MmNodeData& getChild(int index);

private:
    QString m_text;
    std::vector<MmNodeData> m_children;
};

#endif // MMNODEDATA_H

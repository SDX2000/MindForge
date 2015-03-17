#ifndef MMNODEDATA_H
#define MMNODEDATA_H

#include <QCoreApplication>
#include <QWidget>
#include <QFont>
#include <QFontMetrics>
#include <QLabel>
#include <QLayout>
#include <QObject>
#include <QPainter>
#include <QString>
#include <vector>

class MmNodeWidget : public QWidget
{
    Q_OBJECT
public:
    const int MAX_WIDTH = 800;

    explicit MmNodeWidget(QWidget *parent = 0);
    explicit MmNodeWidget(QString text, QWidget *parent=NULL);
    explicit MmNodeWidget(QString text, int id, QWidget *parent=NULL);
    ~MmNodeWidget();


    QString getText() const;
    void setText(QString text);
    void setPos(int x, int y);

    MmNodeWidget* addChild(QString text);
    MmNodeWidget* addChild(QString text, int id);
    MmNodeWidget* getChild(int index);
    void removeLastChild();

    int yMargin();
    int xMargin();
    void setYMargin(int margin);
    void setXMargin(int margin);

    int getId() const;

private:
    void init(QString text, int id);

private:
    std::vector<MmNodeWidget*>  m_children;
    int                         m_id;
    QHBoxLayout                *m_pHBox;
    QVBoxLayout                *m_pVBox;
    QLabel                     *m_pLabel;

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

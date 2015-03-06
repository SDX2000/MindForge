#ifndef MMTEXTEDITOR_H
#define MMTEXTEDITOR_H

#include <QWidget>
#include <QPlainTextEdit>

class MmTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit MmTextEdit(QWidget *parent = 0);
    ~MmTextEdit();
    void keyPressEvent(QKeyEvent * event);

signals:
    void editAccepted();
    void editRejected();

public slots:

};

#endif // MMTEXTEDITOR_H

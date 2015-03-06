#include "mmtextedit.h"

#include<QDebug>

MmTextEdit::MmTextEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{

}

MmTextEdit::~MmTextEdit()
{

}

void MmTextEdit::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Return) {
        emit editAccepted();
        event->accept();
    }
    else if (event->key() == Qt::Key_Escape) {
        emit editRejected();
        event->accept();
    }
    else {
        QPlainTextEdit::keyPressEvent(event);
    }
}

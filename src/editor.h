#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QPlainTextEdit>

class Editor : public QWidget
{
    Q_OBJECT
public:
    Editor(QWidget *parent, QString document_name);
    ~Editor();
    QPlainTextEdit *get_text_edit();
    QString get_document_name();

private:
    QString document_name;

    QWidget *parent;
    QPlainTextEdit *text_edit;
};

#endif // EDITOR_H

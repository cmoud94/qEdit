#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QPlainTextEdit>

class Editor : public QWidget
{
    Q_OBJECT
public:
    Editor(QWidget *parent, QString path, QString name, QString content);
    ~Editor();
    QPlainTextEdit *get_text_edit();
    QString get_document_name();
    QString get_document_path();

private:
    QString document_name;
    QString document_path;

    QWidget *parent;
    QPlainTextEdit *text_edit;
};

#endif // EDITOR_H

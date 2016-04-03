#include "editor.h"

Editor::Editor(QWidget *parent, QString path, QString name, QString content) : QWidget(parent)
{
    this->parent = parent;
    document_path = path;
    document_name = name;
    text_edit = new QPlainTextEdit(parent);
    text_edit->insertPlainText(content);
    text_edit->moveCursor(QTextCursor::Start);
}

Editor::~Editor()
{

}

QPlainTextEdit *Editor::get_text_edit()
{
    return text_edit;
}

QString Editor::get_document_name()
{
    return document_name;
}

QString Editor::get_document_path()
{
    return document_path;
}

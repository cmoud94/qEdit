#include "editor.h"

Editor::Editor(QWidget *parent, QString document_name) : QWidget(parent)
{
    this->parent = parent;
    this->document_name = document_name;
    text_edit = new QPlainTextEdit(parent);
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

#include "editor.h"

#include "mainwindow.h"

Editor::Editor(MainWindow *parent, QString path, QString name, QString content, document_status_t status) : QWidget(parent)
{
    this->parent = parent;
    document_path = path;
    document_name = name;
    document_status = status;
    default_document_status = status;

    text_edit = new QPlainTextEdit(parent->get_tab_widget());
    text_edit->setUndoRedoEnabled(false);
    text_edit->insertPlainText(content);
    text_edit->document()->setModified(false);
    text_edit->setUndoRedoEnabled(true);
    text_edit->moveCursor(QTextCursor::Start);

    parent->update_title(document_name);

    connect(text_edit, &QPlainTextEdit::textChanged, [this] () {
        if(document_status != document_status_t::DOCUMENT_MODIFIED && text_edit->document()->isModified()) {
            document_status = document_status_t::DOCUMENT_MODIFIED;
            emit document_status_changed();
        } else if(!text_edit->document()->isModified()) {
            document_status = default_document_status;
            emit document_status_changed();
        }
    });
    connect(this, SIGNAL(document_status_changed()), this, SLOT(update_title()));
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

document_status_t Editor::get_document_status()
{
    return document_status;
}

document_status_t Editor::get_default_document_status()
{
    return default_document_status;
}

void Editor::set_document_name(QString name)
{
    document_name = name;
}

void Editor::set_document_path(QString path)
{
    document_path = path;
}

void Editor::set_document_status(document_status_t status)
{
    document_status = status;
}

void Editor::set_default_document_status(document_status_t status)
{
    default_document_status = status;
}

void Editor::update_title()
{
    QString title = document_name;
    if(document_status == document_status_t::DOCUMENT_MODIFIED) {
        title += "*";
    }
    parent->get_tab_widget()->setTabText(parent->get_tab_widget()->currentIndex(), title);
    parent->update_title(title);
}

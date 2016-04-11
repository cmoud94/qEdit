#include "editor.h"

#include "mainwindow.h"
#include "linenumbers.h"

Editor::Editor(MainWindow *parent, QString path, QString name, QString content, document_status_t status) : QWidget(parent)
{
    setParent(parent);
    setDocument_path(path);
    setDocument_name(name);
    setDocument_status(status);
    setdefault_document_status(status);

    m_container = new QFrame();

    m_layout = new QHBoxLayout();

    m_text_edit = new QPlainTextEdit();
    m_text_edit->setUndoRedoEnabled(false);
    m_text_edit->insertPlainText(content);
    m_text_edit->document()->setModified(false);
    m_text_edit->setUndoRedoEnabled(true);
    m_text_edit->moveCursor(QTextCursor::Start);

    m_line_widget = new LineNumbers(this, text_edit()->font());

    m_layout->addWidget(m_line_widget->get_line_widget());
    m_layout->addWidget(text_edit());
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    m_container->setLayout(layout());

    parent->update_title(document_name());
    line_widget()->update();

    connect(text_edit(), &QPlainTextEdit::textChanged, [this] () {
        if(document_status() != document_status_t::DOCUMENT_MODIFIED && text_edit()->document()->isModified()) {
            setDocument_status(document_status_t::DOCUMENT_MODIFIED);
        } else if(!text_edit()->document()->isModified()) {
            setDocument_status(default_document_status());
        }
    });
}

Editor::~Editor()
{

}

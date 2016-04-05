#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QPlainTextEdit>

class MainWindow;

enum class document_status_t
{
    DOCUMENT_NEW = 0,
    DOCUMENT_MODIFIED = 1,
    DOCUMENT_SAVED = 2
};

class Editor : public QWidget
{
    Q_OBJECT
public:
    Editor(MainWindow *parent, QString path, QString name, QString content, document_status_t status);
    ~Editor();
    QPlainTextEdit *get_text_edit();
    QString get_document_name();
    QString get_document_path();
    document_status_t get_document_status();
    document_status_t get_default_document_status();
    void set_document_name(QString name);
    void set_document_path(QString path);
    void set_document_status(document_status_t status);
    void set_default_document_status(document_status_t status);

private:
    QString document_name;
    QString document_path;
    document_status_t document_status;
    document_status_t default_document_status;

    MainWindow *parent;
    QPlainTextEdit *text_edit;

private slots:
    void update_title();

signals:
    void document_status_changed();
};

#endif // EDITOR_H

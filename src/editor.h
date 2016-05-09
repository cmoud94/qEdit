#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPlainTextEdit>

class MainWindow;

class Editor : public QWidget
{
    Q_OBJECT

signals:
    void path_changed ( QString new_path );

    void document_status_changed ( int index );

public:
    enum document_status_t
    {
        NEW = 0,
        MODIFIED = 1,
        SAVED = 2
    };

    Editor ( MainWindow* parent, QString title, QString content, QString path, int document_status );

    QWidget* widget ( );

    QPlainTextEdit* text_edit ( );

    static QString title_from_path ( QString path );

    document_status_t document_status ( );

    void set_document_status ( document_status_t new_status );

    document_status_t default_document_status ( );

    void set_default_document_status ( document_status_t new_status );

    QString title ( );

    QString path ( );

    void set_path ( QString new_path );

public slots:

private slots:
    void document_status_change ( );

    void path_change ( QString new_path );

private:
    MainWindow* m_parent;

    QString m_title;

    QString m_path;

    document_status_t m_document_status;

    document_status_t m_default_document_status;

    QWidget* m_widget;

    QHBoxLayout* m_layout;

    QPlainTextEdit* m_text_widget;
};

#endif // EDITOR_H

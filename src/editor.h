#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPlainTextEdit>

class MainWindow;

class Editor : public QWidget
{
    Q_OBJECT

public:
    Editor ( MainWindow* parent, QString title, QString content, QString path, int document_status );

    QWidget* widget ( );

    QPlainTextEdit* text_edit ( );

    static QString title_from_path ( QString path );

    enum document_status_t
    {
        NEW = 0,
        MODIFIED = 1,
        SAVED = 2
    };

public slots:
//    void path_update ( );

private slots:
//    void title_update ( );

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

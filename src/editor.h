#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QHBoxLayout>

class MainWindow;
class LineNumbers;

enum class document_status_t
{
    DOCUMENT_NEW = 0,
    DOCUMENT_MODIFIED = 1,
    DOCUMENT_SAVED = 2
};

class Editor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString document_name READ document_name WRITE setDocument_name NOTIFY document_nameChanged)
    Q_PROPERTY(QString document_path READ document_path WRITE setDocument_path NOTIFY document_pathChanged)
    Q_PROPERTY(document_status_t document_status READ document_status WRITE setDocument_status NOTIFY document_statusChanged)
    Q_PROPERTY(document_status_t default_document_status READ default_document_status WRITE setdefault_document_status NOTIFY default_document_statusChanged)

    Q_PROPERTY(MainWindow* parent READ parent)
    Q_PROPERTY(LineNumbers* line_widget READ line_widget)
    Q_PROPERTY(QPlainTextEdit* text_edit READ text_edit)
    Q_PROPERTY(QFrame* container READ container)
    Q_PROPERTY(QHBoxLayout* layout READ layout)

    QString m_document_name;

    QString m_document_path;

    document_status_t m_document_status;

    document_status_t m_default_document_status;

    MainWindow* m_parent;

    LineNumbers* m_line_widget;

    QPlainTextEdit* m_text_edit;

    QFrame *m_container;

    QHBoxLayout *m_layout;

public:
    Editor(MainWindow *parent, QString path, QString name, QString content, document_status_t status);
    ~Editor();

    QString document_name() const
    {
        return m_document_name;
    }
    QString document_path() const
    {
        return m_document_path;
    }

    document_status_t document_status() const
    {
        return m_document_status;
    }

    document_status_t default_document_status() const
    {
        return m_default_document_status;
    }

    MainWindow* parent() const
    {
        return m_parent;
    }

    LineNumbers* line_widget() const
    {
        return m_line_widget;
    }

    QPlainTextEdit* text_edit() const
    {
        return m_text_edit;
    }

    QFrame* container() const
    {
        return m_container;
    }

    QHBoxLayout* layout() const
    {
        return m_layout;
    }

public slots:
    void setDocument_name(QString document_name)
    {
        if (m_document_name == document_name)
            return;

        m_document_name = document_name;
        emit document_nameChanged(document_name);
    }
    void setDocument_path(QString document_path)
    {
        if (m_document_path == document_path)
            return;

        m_document_path = document_path;
        emit document_pathChanged(document_path);
    }

    void setDocument_status(document_status_t document_status)
    {
        if (m_document_status == document_status)
            return;

        m_document_status = document_status;
        emit document_statusChanged(document_status);
    }

    void setdefault_document_status(document_status_t default_document_status)
    {
        if (m_default_document_status == default_document_status)
            return;

        m_default_document_status = default_document_status;
        emit default_document_statusChanged(default_document_status);
    }

signals:
    void document_nameChanged(QString document_name);
    void document_pathChanged(QString document_path);
    void document_statusChanged(document_status_t document_status);
    void default_document_statusChanged(document_status_t default_document_status);
};

#endif // EDITOR_H

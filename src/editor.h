#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>

class MainWindow;
class QFrame;
class QHBoxLayout;
class QPlainTextEdit;

class Editor : public QWidget
{
    Q_OBJECT

public:
    Editor ( MainWindow* parent, QString title, QString content, QString path );

public slots:


private slots:


private:
    MainWindow* m_parent;

    QString m_title;

    QString m_path;

    QFrame* m_frame;

    QHBoxLayout* m_layout;

    QPlainTextEdit* m_text_widget;
};

#endif // EDITOR_H

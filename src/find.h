#ifndef FIND_H
#define FIND_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWindow;

class Find : public QDialog
{
    Q_OBJECT

public:
    Find ( MainWindow* parent, bool replace );

private:
    MainWindow* m_parent;

    QVBoxLayout* m_layout;

    QLineEdit* m_line_edit_find;

    QLineEdit* m_line_edit_replace;

    QCheckBox* m_match_word;

    QCheckBox* m_ignore_case;

    QCheckBox* m_regexp;

    QCheckBox* m_backwards;

    QPushButton* m_btn_close;

    QPushButton* m_btn_replace;

    QPushButton* m_btn_replace_all;

    QPushButton* m_btn_find;
};

#endif // FIND_H

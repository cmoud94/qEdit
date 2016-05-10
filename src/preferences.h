#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QGroupBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QList>

class MainWindow;

class Preferences : public QDialog
{
    Q_OBJECT

public:
    Preferences ( MainWindow* parent );

    ~Preferences ( );

private:
    QString m_config_file_path = ":/files/files/supported_file_extensions.txt";

    QList< QString >* m_config_keys;

    QList< QString >* m_config_default_values;

    QList< QString >* m_config_values;

    MainWindow* m_parent;

    QVBoxLayout* m_layout;

    QHBoxLayout* m_layout_btns;

    QGroupBox* m_text_wrap_group;

    QCheckBox* m_text_wrap_chkbox;

    QCheckBox* m_text_wrap_words_chkbox;

    QGroupBox* m_ln_nums_group;

    QCheckBox* m_ln_nums_chkbox;

    QGroupBox* m_curr_ln_group;

    QCheckBox* m_curr_ln_chkbox;

    QGroupBox* m_tab_width_group;

    QSpinBox* m_tab_width_spinbox;

    QGroupBox* m_font_config_group;

    QPushButton* m_font_config_btn;

    QPushButton* m_def_geometry_btn;

    QPushButton* m_default_btn;

    QPushButton* m_close_btn;

    QString read_config_file ( );

    void write_config_file ( );
};

#endif // PREFERENCES_H

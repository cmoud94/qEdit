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
#include <QSettings>
#include <QFontDialog>
#include <QFont>
#include <QDebug>

class MainWindow;

class Preferences : public QDialog
{
    Q_OBJECT

public:
    Preferences ( MainWindow* parent );

    ~Preferences ( );

private slots:
    void config_save ( );

    void font_config ( );

private:
    QString m_company = "cmoud94";

    QString m_application = "qEdit";

    QSettings* m_settings;

    QList< QString >* m_config_keys;

    QList< QVariant >* m_config_default_values;

    QList< QVariant >* m_config_values;

    MainWindow* m_parent;

    QVBoxLayout* m_layout;

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

    void config_read ( );

    void update_widgets ( );

    void get_widgets_values ( );
};

#endif // PREFERENCES_H

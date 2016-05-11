#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QTabWidget>
#include <QStatusBar>
#include <QList>
#include <QIcon>
#include <QMessageBox>
#include <QToolButton>
#include <QFileDialog>
#include <QVariant>
#include <QSettings>
#include <QDebug>

class Editor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow ( QMainWindow* parent = 0 );

    ~MainWindow ( );

    QTabWidget* tab_widget ( );

    QList< Editor* >* editors ( );

public slots:
    void window_title_update ( QString new_title );

    void document_status_changed ( int index );

private slots:
    void file_new ( );

    void file_open ( );

    void file_save ( );

    void file_save_as ( );

    void file_close ( );

    void file_quit ( );

    void edit_undo ( );

    void edit_redo ( );

    void edit_cut ( );

    void edit_copy ( );

    void edit_paste ( );

    void edit_preferences ( );

    void search_find ( );

    void search_replace ( );

    void help ( );

    void help_about ( );

    void tab_close ( int index );

    void tab_changed ( int index );

    void config_changed ( QList< QVariant >* new_config );

private:
    const QString WIN_TITLE = "qEdit";

    const int WIN_MIN_WIDTH = 400;

    const int WIN_MIN_HEIGHT = 300;

    QString m_window_title;

    QMenuBar* m_menu_bar;

    QMenu* m_menu_file;

    QMenu* m_menu_edit;

    QMenu* m_menu_search;

    QMenu* m_menu_help;

    QToolBar* m_tool_bar;

    QList< QIcon >* m_tool_bar_icons;

    QTabWidget* m_tab_widget;

    QList< Editor* >* m_editors;

    QStatusBar* m_status_bar;

    QString m_file_type_filter;

    QString m_default_file_type;

    QList< QVariant > m_config;

    QList< QString > m_config_keys;

    void menu_bar_init ( );

    void tool_bar_init ( );

    void tab_widget_init ( );

    void status_bar_init ( );

    void tab_new ( QString title, QString content, QString path, int document_status );

    int dialog_show ( QString text, QString secondary_text, int icon, int buttons, int default_button );

    void load_supported_file_types ( );

    void file_write ( QString path, Editor* editor );

    void closeEvent ( QCloseEvent* event );
};

#endif // MAINWINDOW_H
